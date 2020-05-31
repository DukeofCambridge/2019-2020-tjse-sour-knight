//���ǰ�ȫ��ͼ

#include "Scene/startScene.h"
#include "Scene/startScene2.h"
#include "Scene/firstStage.h"
#include"Scene/chooseKnightScene.h"

USING_NS_CC;

Scene* firstStage::createScene()
{

	return firstStage::create();
}

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}


bool firstStage::init()
{

	if (!Scene::init())
	{
		return false;
	}

////////////////////////////����ΪfirstStage���Ա������ʼ��/////////////////////////////////

	this->setKnightBeenSelected(false);

////////////////////////////����Ϊ��ͼ��������///////////////////////////////////////////////
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	TMXTiledMap* map = TMXTiledMap::create("Backgrounds/safeMap.tmx");//��ͼ
	//�ı�λ��
	
	//��ȡ��ͼ����
	addChild(map, 0);
	//�ı��ͼ��С������Ϊ����
	
	//��ȡͼ������
	auto sceneLayer = map->getLayer("ground");
	auto layerProperties = sceneLayer->getProperties();
	CCLOG("layer pro:%s", layerProperties["type"].asString().c_str());
	//��ȡͼ������
	
	
	//��ȡ��������
	auto objectGroup = map->getObjectGroup("object");
	auto obj = objectGroup->getObject("knight");

	CCLOG("tile pro:%s", obj["type"].asString().c_str());

	//�޸�ָ���������ɫ
	auto colorObj = objectGroup->getObject("pass");
	auto colorObjX = colorObj["x"].asInt() / 32;
	auto colorObjY = colorObj["y"].asInt() / 32;
	auto colorObjW = colorObj["width"].asInt() / 32;
	auto colorObjH = colorObj["height"].asInt() / 32;
	for (int x = colorObjX; x < colorObjX + colorObjW; x++) {
		for (int y = colorObjY; y < colorObjY + colorObjH; y++) {
			auto sprite = sceneLayer->getTileAt(Vec2(x, map->getMapSize().height - y));
			sprite->setColor(Color3B(225, 0, 0));
		}
	}
	
/////////////////////////////////����Ϊ������������////////////////////////////////////

	auto knight= Knight::create("Heros/unchosenKnight.png", "0", REMOTE);
	
	knight->setPosition(Vec2(640, 480));
	knight->setTag(TAG_OF_KNIGHT);
	this->addChild(knight);
	this->scheduleUpdate();

	return true;
}




void firstStage::onEnter()
{
	Scene::onEnter();
/////////////////////////////����Ϊ��ɫѡ�������///////////////////////////////////
	
	auto KnightSelectedListener = EventListenerTouchOneByOne::create();
	KnightSelectedListener->setSwallowTouches(true);
	KnightSelectedListener->onTouchBegan = CC_CALLBACK_2(firstStage::touchBegan, this);
	
	KnightSelectedListener->onTouchEnded = CC_CALLBACK_2(firstStage::touchEnded, this);
	
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

}


void firstStage::onExit()
{
	Scene::onExit();

}




void firstStage::update(float delta)
{
	if (this->_knightBeenSelected == true)
	{
		int offsetX = 0, offsetY = 0;

		if (keys[EventKeyboard::KeyCode::KEY_D])
		{
			offsetX = 5;
		}
		if (keys[EventKeyboard::KeyCode::KEY_A])
		{
			offsetX = -5;
		}
		if (keys[EventKeyboard::KeyCode::KEY_S])
		{
			offsetY = -5;
		}
		if (keys[EventKeyboard::KeyCode::KEY_W])
		{
			offsetY = 5;
		}

		Node* knight = this->getChildByTag(TAG_OF_KNIGHT);

		auto moveTo = MoveTo::create(0.3, Vec2(knight->getPositionX() + offsetX, knight->getPositionY() + offsetY));

		knight->runAction(moveTo);//��ɫ�ƶ�
	}
}


bool firstStage::touchBegan(Touch* touch, Event* event)
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

void firstStage::touchEnded(Touch* touch, Event* event)
{
	if (this->_knightBeenSelected == false)
	{
		auto sc = chooseKnightScene::create();
		auto reScene = TransitionProgressInOut::create(0.3f, sc);
		
		Director::getInstance()->replaceScene(reScene);
	}
}