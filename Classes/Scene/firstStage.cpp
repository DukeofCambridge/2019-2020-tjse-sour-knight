//���ǰ�ȫ��ͼ

#include "Scene/startScene.h"
#include "Scene/startScene2.h"
#include "Scene/firstStage.h"
#include"Scene/chooseKnightScene.h"
#include"Settings/SoundAndMusic.h"
#include"Settings/pauseControl.h"
#include"Settings/CreateDoor.h"
#include"Function/CommonFunction.h"


Scene* firstStage::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vec2(0.0f, 0.0f));//ȡ��������
	scene->setTag(TAG_OF_FIRST_STAGE_SCENE);
	auto layer = firstStage::create();
	scene->addChild(layer, 0);

// ////////////////////////////������ͣ��ť////////////////////////////////////////////
	auto pauseMenuItem = MenuItemImage::create(
		"Buttons/buttonPause.png", "Buttons/buttonPauseClicked.png", CC_CALLBACK_1(firstStage::menuPauseCallback, layer));
	pauseMenuItem->setPosition(Vec2(1200, 900));
	float length = 120;
	auto buttonSize = pauseMenuItem->getContentSize();
	float scaleSize = length / buttonSize.width;
	pauseMenuItem->setScale(scaleSize);

	auto startMenu = Menu::create(pauseMenuItem, NULL);
	startMenu->setPosition(Vec2::ZERO);
	scene->addChild(startMenu,1);
	// //////////////////////////////////////////////////////////////////////////////
	
	return scene;
}

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool firstStage::init()
{

	if (!Layer::init())
	{
		return false;
	}
////////////////////////////����ΪfirstStage���Ա������ʼ��/////////////////////////////////

	this->setKnightBeenSelected(false);
	this->setInAttackRange(false);
////////////////////////////����Ϊ������������(����)///////////////////////////////////////////////
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto body = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 5.0f);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	edgeNode->setPhysicsBody(body);
	this->addChild(edgeNode);
	setTouchEnabled(true);
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
///////////////////////////����Ϊ���õ�ͼ����/////////////////////////
	 map = TMXTiledMap::create("Backgrounds/safeMap.tmx");//��ͼ
	//�ı�λ��

	map->setScale(2);

	//��ȡ��ͼ����
	addChild(map, 0);

	//���ô�����
	auto door = setDoor(1600, 636, 200);
	this->addChild(door);
	
	TMXObjectGroup* group = map->getObjectGroup("obj");

	ValueMap spawnPoint = group->getObject("player");

	float x = spawnPoint["x"].asFloat();

	float y = spawnPoint["y"].asFloat();

	collidable = map->getLayer("collidable");

	collidable->setVisible(false);


	this->setTag(TAG_OF_FIRST_STAGE_LAYER);

/////////////////////////////////����Ϊ������������////////////////////////////////////

	auto knight= Sprite::create("Heroes/unchosenKnight.png");//ע�����ǽ�ɫδ��ѡ��ʱ��ͼƬ����Ϊһ����ͼ����
// //������ײ����
// //
	knight->setPosition(Vec2(640, 480));
	log("%f", knight->getPosition().x);
	log("%f", knight->getPosition().y);

	knight->setTag(TAG_OF_KNIGHT);

	this->addChild(knight);
		
	this->scheduleUpdate();
	return true;
}

void firstStage::onEnter()//ע�����������������
{
	Layer::onEnter();
/////////////////////////////����Ϊ��ɫѡ�������///////////////////////////////////
	
	auto KnightSelectedListener = EventListenerTouchOneByOne::create();
	KnightSelectedListener->setSwallowTouches(true);
	KnightSelectedListener->onTouchBegan = CC_CALLBACK_2(firstStage::chooseKnightTouchBegan, this);
	
	KnightSelectedListener->onTouchEnded = CC_CALLBACK_2(firstStage::chooseKnightTouchEnded, this);
	
	// ע�������
	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(KnightSelectedListener, getChildByTag(TAG_OF_KNIGHT));



	/////////////////////////////����Ϊ��ɫ�ƶ�������///////////////////////////////////
	auto knightMoveListener = EventListenerKeyboard::create();

	knightMoveListener->onKeyPressed = [=](EventKeyboard::KeyCode code, Event* e)
	{
		keys[code] = true;
	};

	knightMoveListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event)
	{
		keys[keyCode] = false;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(knightMoveListener, this);

		playMusic("sound/SafeMapBGM.mp3", true);	
}

void firstStage::onEnterTransitionDidFinish()
{
Layer::onEnterTransitionDidFinish();
	log("firstStage onEnterTransitionDidFinish");
}

void firstStage::onExitTransitionDidStart()
{
	Layer::onExitTransitionDidStart();
	log("firstStage onExitTransitionDidStart");
}

void firstStage::onExit()//ע��������
{
	Layer::onExit();

}

void firstStage::cleanup()
{
	Layer::cleanup();
	log("firstStage cleanup");
	//playMusic("sound/SafeMapBGM.mp3", true, 1);
}

void firstStage::menuPauseCallback(cocos2d::Ref* pSender)//��ͣ��ť�Ļص�
{
	log("menuPauseCallback touched");
	//SimpleAudioEngine::getInstance()->pauseBackgroundMusic();

	auto scene = Pause::createScene();
	Director::getInstance()->pushScene(scene);
	playSound("sound/ClickSound.mp3");
}

bool firstStage::chooseKnightTouchBegan(Touch* touch, Event* event)//ѡ��Ӣ��-��ʿ���ж��Ƿ�����Ӧͼ�꣩
{
	//��ȡ�¼����󶨵�target
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
	Size s = target->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.height);

	//������Χ�жϼ��,ѡ���ɫʱ�ĳ����л�
	if (rect.containsPoint(locationInNode))
	{
		return true;
	}
	return false;
}

void firstStage::chooseKnightTouchEnded(Touch* touch, Event* event)//ѡ��Ӣ��
{
	if (this->_knightBeenSelected == false)
	{
		auto sc = chooseKnightScene::create();
		auto reScene = TransitionProgressInOut::create(0.3f, sc);
		playSound("sound/ClickSound.mp3");
		Director::getInstance()->replaceScene(reScene);
	}
}


bool firstStage::onTouchBegan(Touch* touch, Event* event)//���������ʿ����
{
	if (this->getKnightBeenSelected() && this->getKnight()->getMP())
	{
		Vec2 p = this->getWeapon()->getPosition();
		auto bullet = Bullet::create("Bullets/bullet1.png", 3, NORMAL);
/// ///////////������ײ����
		auto body = PhysicsBody::createBox(bullet->getContentSize());
		body->setCategoryBitmask(MY_BULLET_1);//0010
		body->setCollisionBitmask(MY_BULLET_2);//0001
		bullet->setPhysicsBody(body);
		bullet->setPosition(p);
		this->addChild(bullet);
		
/// ///////////////����Ϊ������Χ���޵��˵Ĺ�����ʽ���������ĳ�����򹥻�
			float tempAngle = CCRANDOM_0_1() * 2 * PI;
			float x = 250 * cos(tempAngle);
			float y = 250 * sin(tempAngle);
			bullet->runAction(Sequence::create(MoveBy::create(0.3f, Vec2(x, y)), CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, bullet)), NULL));
			updateInformationMP(this ,this->getKnight());
			

		return false;
	}
	return false;
}


void firstStage::removeFromParent(Node* bullet)//ɾ���ӵ��Ļص�����
{
	bullet->removeFromParent();
}

void firstStage::update(float delta)
{
	if (this->_knightBeenSelected)
	{
		knightMove();

	}
}

void firstStage::knightMove()//������update��ĺ�����ʵ����ʿ��ɫ���ƶ�
{
	Point playerPos = this->getKnight()->getPosition();


	if (keys[EventKeyboard::KeyCode::KEY_D])
	{
		playerPos.x += map->getTileSize().width / 4;

		this->getKnight()->runAction(FlipX::create(false));
		this->getWeapon()->runAction(FlipX::create(false));
	}
	if (keys[EventKeyboard::KeyCode::KEY_A])
	{
		playerPos.x -= map->getTileSize().width / 4;

		this->getKnight()->runAction(FlipX::create(true));
		this->getWeapon()->runAction(FlipX::create(true));
	}
	if (keys[EventKeyboard::KeyCode::KEY_S])
	{
		playerPos.y -= map->getTileSize().height / 4;
	}
	if (keys[EventKeyboard::KeyCode::KEY_W])
	{
		playerPos.y += map->getTileSize().height / 4;
	}


	this->setPlayerPosition(playerPos);
	this->screenRoll(playerPos);




}

void firstStage::setPlayerPosition(Point position)

{
	if (this->getKnightBeenSelected())
	{
		//�����ص�����ת��Ϊ��Ƭ����

		Point tileCoord = this->transPoision(position);
		//tileCoord.x = tileCoord.x / 2;
		//tileCoord.y = (_tileMap->getMapSize().height-tileCoord.y)/2;


			//�����Ƭ��GID

		const int tileGid = collidable->getTileGIDAt(tileCoord);

		if (tileGid > 0) {


			Value prop = map->getPropertiesForGID(tileGid);

			ValueMap propValueMap = prop.asValueMap();


			std::string collision = propValueMap["Collidable"].asString();

			std::string pass = propValueMap["pass"].asString();

			if (collision == "true") { //��ײ���ɹ�									

				return;

			}
			if (pass == "true") 
			{
				auto scene = Level01::createScene();
				////Ԥ����
				scene->removeChildByTag(TAG_OF_LEVEL_01);
				//

			  auto stage = Level01::create();

			    auto knight=Knight::create("Heroes/knight1.1.png",this->getKnight());
				auto weapon =Weapon::create("Weapons/weaponGun.png",this->getWeapon());

				knight->setPosition(Vec2(640, 480));
				weapon->setPosition(Vec2(640, 455));

				knight->setTag(TAG_OF_KNIGHT);
				weapon->setTag(TAG_OF_KNIGHT_INITIAL_WEAPON);
				//stage->setTag(TAG_OF_LEVEL_01);

				//������ײ����
				auto heroBody = PhysicsBody::createBox(knight->getContentSize());
				heroBody->setCategoryBitmask(MY_HERO_1);
				heroBody->setCollisionBitmask(MY_HERO_2);
				knight->setPhysicsBody(heroBody);

				auto weaponBody = PhysicsBody::createBox(weapon->getContentSize());
				weaponBody->setCategoryBitmask(WEAPON_1);
				weaponBody->setCollisionBitmask(WEAPON_2);
				weapon->setPhysicsBody(weaponBody);
				////��ɫ�����
				stage->addChild(knight);
				stage->addChild(weapon);
		        stage->setKnight(knight);
				stage->setWeapon(weapon);
				if (this->getKnightBeenSelected())
				{
					stage->setKnightBeenSelected(true);
				}
				scene->addChild(stage, 0);

				//////////����InformationBox
				createInformationBox(stage, knight);


				
				auto reScene = TransitionProgressOutIn::create(0.5f, scene);
				Director::getInstance()->replaceScene(reScene);

				//CCLOG("aaaaaaaaaaaaaaa");
			}

		}
		this->getKnight()->setPosition(position);
		Point pos = Point(position.x , position.y - 25);
		this->getWeapon()->setPosition(pos);
	}

}


Point firstStage::transPoision(Point pos)

{
	if (this->getKnightBeenSelected())
	{
		int x = 0.5 * pos.x / map->getTileSize().width;
		int y = ((map->getMapSize().height * map->getTileSize().height) - 0.5 * pos.y) /

		map->getTileSize().height;

		return Point(x, y);
	}

}


void firstStage::screenRoll(Point position)

{
	if (this->getKnightBeenSelected())
	{
		Size visibleSize = Director::getInstance()->getVisibleSize();


		//��Ļ���ĵ�

		Point pointA = Point(visibleSize.width / 2, visibleSize.height / 2);

		Point pointB = position;
		//position

		//��ͼ�ƶ�ƫ����

		Point offset = (pointA - pointB);

		this->setPosition(offset);
	}

}