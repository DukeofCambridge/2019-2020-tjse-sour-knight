#include "Scene/Level02.h"
#include "Scene/Level03.h"
#include "Scene/Level04.h"

Scene* Level03::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vec2(0.0f, 0.0f));//ȡ��������

	auto layer = Level03::create();
	scene->addChild(layer, 0);
	// ////////////////////////////������ͣ��ť////////////////////////////////////////////
	auto pauseMenuItem = MenuItemImage::create(
		"Buttons/buttonPause.png", "Buttons/buttonPauseClicked.png", CC_CALLBACK_1(Level03::menuPauseCallback, layer));
	pauseMenuItem->setPosition(Vec2(1200, 900));
	float length = 120;
	auto buttonSize = pauseMenuItem->getContentSize();
	float scaleSize = length / buttonSize.width;
	pauseMenuItem->setScale(scaleSize);

	auto startMenu = Menu::create(pauseMenuItem, NULL);
	startMenu->setPosition(Vec2::ZERO);
	scene->addChild(startMenu, 1);
	// //////////////////////////////////////////////////////////////////////////////

	return scene;
}

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}


bool Level03::init()
{

	if (!Layer::init())
	{
		return false;

	}
	////////////////////////////����ΪLavel01���Ա������ʼ��/////////////////////////////////

	this->setKnightBeenSelected(false);
	this->setKnight(nullptr);
	this->setWeapon(nullptr);
	this->setBullet(nullptr);
	this->setInAttackRange(false);

	smallMap = Sprite::create("Props/smallMap2.png");
	smallK = Sprite::create("Props/star.png");

	////////////////////////////����Ϊ������������(����)///////////////////////////////////////////////
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	auto body = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 5.0f);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	edgeNode->setPhysicsBody(body);
	this->addChild(edgeNode);
	setTouchEnabled(true);
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	///////////////////////////����Ϊ���õ�ͼ����/////////////////////////

	map = TMXTiledMap::create("Backgrounds/theM3.tmx");	//��ͼ��
	map->setScale(2);
	addChild(map, 0);


	TMXObjectGroup* group = map->getObjectGroup("obj");
	ValueMap spawnPoint = group->getObject("player");
	float x = spawnPoint["x"].asFloat();
	float y = spawnPoint["y"].asFloat();


	smallK->setPosition(x + 2600, y + 2600);
	smallMap->setPosition(x + 1500, y + 1500);
	addChild(smallMap);
	addChild(smallK);


	collidable = map->getLayer("collidable");
	collidable->setVisible(false);
	this->setTag(TAG_OF_LEVEL_03);
	/////////////////////////���������

	ValueMap spawnPoint1;
	Box* box;
	std::string boxNum[5] = { "box0","box1","box2","box3","box4" };//box4��װ�����ı���
	for (int i = 0; i < 5; i++) {
		spawnPoint1 = group->getObject(boxNum[i]);
		box = Box::create("Props/box.png", 0, 0, 0, 0, "Weapons/weaponBasketball.png");
		boxVec.pushBack(box);
		boxVec.at(i)->setPosition(2 * spawnPoint1["x"].asFloat(), 2 * spawnPoint1["y"].asFloat());
		boxPositionVec.push_back(Vec2(2 * spawnPoint1["x"].asFloat(), 2 * spawnPoint1["y"].asFloat()));
		addChild(boxVec.at(i));

		boxVec.at(i)->setVisible(false);
	}
	boxVec.at(4)->setVisible(true);
	boxVec.at(2)->setVisible(true);
	///////////////////////////////////////////////////����ΪС�ֵ�����
		//����С��

	//���봫����
	ValueMap doorPoint = group->getObject("transfer");

	float xDoor = 2 * doorPoint["x"].asFloat();

	float yDoor = 2 * doorPoint["y"].asFloat();

	auto door = setDoor(xDoor, yDoor, 200);
	door->setTag(TAG_OG_SAFEMAP_DOOR);
	this->addChild(door);
	door->setVisible(false);

	char monsters[5][4] = { "m1","m2" ,"m3" ,"m4" ,"m5" };

	char monstersGroup2[5][4] = { "m6","m7" ,"m8" ,"m9" ,"m10" };

	char monstersGroup1[5][4] = { "m11","m12" ,"m13" ,"m14" ,"m15" };

	char monstersGroup3[5][4] = { "m16","m17" ,"m18" ,"m19" ,"m20" };

	createMonster(monsters, "Creeps/monster6.png", 0);

	createMonster(monstersGroup2, "Creeps/monster7.png", 5);

	createMonster(monstersGroup1, "Creeps/monster8.png", 10);

	createMonster(monstersGroup3, "Creeps/monster9.png", 15);

	createMonster(monsters, "Creeps/monster10.png", 20);

	createMonster(monstersGroup2, "Creeps/monster9.png", 25);

	//������Ϣ��ʼ��
	deadCreeps = 0;
	for (int i = 0; i < 15; i++)
	{
		creepDieArr[i] = false;
	}

	for (int j = 0; j < 4; j++)
	{
		littleMapClear[j] = 0;
		littleMapWave[j] = 0;
	}

	// ////////////////////////////////////////////////////////////////////
	this->schedule(schedule_selector(Level03::enemyAttackUpdate), 1.0f, kRepeatForever, 0);//���˵Ĺ���
	this->schedule(schedule_selector(Level03::enemyMoveUpdate), 2.0f, -1, 0);//���˵��ƶ�
	this->schedule(schedule_selector(Level03::armorRecoverUpdate), 2.0f, kRepeatForever, 0);//���׵Ļָ�
	this->schedule(schedule_selector(Level03::heroDieUpdate), 3.0f, kRepeatForever, 2.0f);
	this->schedule(schedule_selector(Level03::groundAttackUpdate), 0.5f, kRepeatForever, 0);

	this->scheduleUpdate();

	//���������ߵĳ�ʼ��
	initWeapon();
	initProps();

	return true;

}

void Level03::createMonster(char arr[5][4], const std::string& location, int num)
{
	int tagArr[5] = { 55 + num,56 + num,57 + num,58 + num,59 + num };
	for (int i = 0; i < 5; i++)
	{
		TMXObjectGroup* group = map->getObjectGroup("obj");

		ValueMap mPoint = group->getObject(arr[i]);

		float x = 2 * mPoint["x"].asFloat();

		float y = 2 * mPoint["y"].asFloat();

		Creep* monsterTemp;
		if (num / 5 == 0)
			monsterTemp = Creep::create(location, NORMAL, ENEMY_REMOTE2, CREEP_HP_3, MONSTER_ATTACK_MEDIUM, true);
		else if (num / 5 == 1)
			monsterTemp = Creep::create(location, NORMAL, ENEMY_REMOTE2, CREEP_HP_4, MONSTER_ATTACK_MEDIUM, true);
		else if (num / 5 == 2)
			monsterTemp = Creep::create(location, NORMAL, ENEMY_REMOTE2, CREEP_HP_4, MONSTER_ATTACK_MEDIUM, true);
		else if (num / 5 == 3)
			monsterTemp = Creep::create(location, NORMAL, ENEMY_REMOTE2, CREEP_HP_4, MONSTER_ATTACK_MEDIUM, true);
		else if (num / 5 == 4)
			monsterTemp = Creep::create(location, NORMAL, ENEMY_REMOTE2, CREEP_HP_4, MONSTER_ATTACK_MEDIUM, false);
		else if (num / 5 == 5)
			monsterTemp = Creep::create(location, NORMAL, ENEMY_REMOTE2, CREEP_HP_3, MONSTER_ATTACK_MEDIUM, false);

		auto body = PhysicsBody::createBox(monsterTemp->getContentSize());
		body->setCategoryBitmask(ENEMY_1);
		body->setCollisionBitmask(0);
		body->setContactTestBitmask(ENEMY_2);
		monsterTemp->setPhysicsBody(body);


		monsterTemp->setPosition(x, y);

		CCLOG("%f %f", x, y);

		monsterTemp->setTag(tagArr[i]);
		this->addChild(monsterTemp);

		if (!monsterTemp->getActive())
		{
			monsterTemp->setVisible(false);

		}


		creepsVec.pushBack(monsterTemp);
	}
}

void Level03::creepDie(Creep* creep)
{


	int tag = creep->getTag();

	if ((tag >= TAG_OF_MONSTER_1) && (tag <= TAG_OF_MONSTER_5))
	{
		creep->initWithFile("Creeps/monster6Dead.png");
		creepDieArr[tag - 55] = true;
		littleMapClear[0]++;
		deadCreep[0]++;
		deadCreeps++;
	}

	else if ((tag >= TAG_OF_MONSTER_1 + 5) && (tag <= TAG_OF_MONSTER_5 + 5))
	{
		creep->initWithFile("Creeps/monster7Dead.png");
		creepDieArr[tag - 55] = true;
		littleMapClear[1]++;
		deadCreep[1]++;
		deadCreeps++;

	}

	else if ((tag >= TAG_OF_MONSTER_1 + 10) && (tag <= TAG_OF_MONSTER_5 + 10))
	{
		creep->initWithFile("Creeps/monster8Dead.png");
		creepDieArr[tag - 55] = true;
		littleMapClear[2]++;
		deadCreep[2]++;
		deadCreeps++;
	}

	else if ((tag >= TAG_OF_MONSTER_1 + 15) && (tag <= TAG_OF_MONSTER_5 + 15))
	{
		creep->initWithFile("Creeps/monster9Dead.png");
		creepDieArr[tag - 55] = true;
		littleMapClear[2]++;
		deadCreep[2]++;
		deadCreeps++;
	}

	else if ((tag >= TAG_OF_MONSTER_1 + 20) && (tag <= TAG_OF_MONSTER_5 + 20))
	{
		creep->initWithFile("Creeps/monster10Dead.png");
		creepDieArr[tag - 55] = true;
		littleMapClear[0]++;
		deadCreep[0]++;
		deadCreeps++;
	}
	else if ((tag >= TAG_OF_MONSTER_1 + 25) && (tag <= TAG_OF_MONSTER_5 + 25))
	{
		creep->initWithFile("Creeps/monster9Dead.png");
		creepDieArr[tag - 55] = true;
		littleMapClear[1]++;
		deadCreep[1]++;
		deadCreeps++;
	}

	for (int i = 0; i < 2; i++)
	{
		if (littleMapClear[i] >= 5)
		{
			CCLOG("%d", i);
			littleMapClear[i] = 0;

			if (littleMapWave[i] == 0)
			{

				for (int j = 20 + i * 5; j < 25 + i * 5; j++)
				{
					Creep* monster = creepsVec.at(j);
					monster->setActive(true);
					monster->setVisible(true);

				}

			}
			littleMapWave[i]++;
		}
	}
	if (deadCreep[1] == 10) {

		boxVec.at(0)->setVisible(true);
		boxVec.at(0)->setOpen(true);

	}
	if (deadCreep[0] == 10) {

		boxVec.at(1)->setVisible(true);
		boxVec.at(1)->setOpen(true);

	}
	if (deadCreep[2] == 10) {

		boxVec.at(3)->setVisible(true);
		boxVec.at(3)->setOpen(true);
	}

	if (deadCreeps >= 30)
	{
		allClear = true;
		auto door = this->getChildByTag(TAG_OG_SAFEMAP_DOOR);
		door->setVisible(true);
	}
}


void Level03::onEnter()//ע�����������������
{
	Layer::onEnter();

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

	/////////////////////////////����Ϊ��ײ������/////////////////////////////////////////
	auto monsterListener = EventListenerPhysicsContact::create();
	monsterListener->onContactBegin = [&](PhysicsContact& contact)
	{
		auto bullet = static_cast<Bullet*>(contact.getShapeA()->getBody()->getNode());
		auto monster = static_cast<Creep*>(contact.getShapeB()->getBody()->getNode());
		if (bullet && bullet->getTag() == TAG_OF_BULLET_01 && monster && (monster->getTag() >= TAG_OF_MONSTER_1) && (monster->getTag() <= MAX_TAG_OF_MONSTER) && (monster->getActive()))
		{
			if (!monster->getAlreadyDead())
			{
				monster->setColor(Color3B::RED);
				monster->takeDamage(bullet);
				//DEBUFF
				if (bullet->getDebuffType() == BURN)
				{
					float seed = CCRANDOM_0_1();
					if (seed >= 0.5)
					{
						monster->setReleaseDebuff(BURN);
						monster->setColor(Color3B::RED);
					}
				}
				else if (bullet->getDebuffType() == FROST)
				{
					float seed = CCRANDOM_0_1();
					if (seed >= 0.5)
					{
						monster->setReleaseDebuff(FROST);
						monster->setColor(Color3B::BLUE);
					}
				}
				bullet->removeFromParent();

				if (monster->getAlreadyDead())
				{
					creepDie(monster);
				}
			}
		}

		return true;
	};
	monsterListener->onContactPreSolve = [](PhysicsContact& contact, PhysicsContactPreSolve& solve)
	{

		return true;
	};
	monsterListener->onContactPostSolve = [](PhysicsContact& contact, const PhysicsContactPostSolve& solve)
	{
	};

	monsterListener->onContactSeparate = [&](PhysicsContact& contact)
	{
		auto monster = (Creep*)contact.getShapeB()->getBody()->getNode();
		if (monster && (monster->getTag() >= TAG_OF_MONSTER_1) && (monster->getTag() <= MAX_TAG_OF_MONSTER))
			monster->setColor(Color3B::WHITE);
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(monsterListener, 1);

	// ///////////////////////////////////////////////////////////�ڶ�����ײ������

	auto heroListener = EventListenerPhysicsContact::create();
	heroListener->onContactBegin = [&](PhysicsContact& contact)
	{
		auto bullet = static_cast<Bullet*>(contact.getShapeA()->getBody()->getNode());
		auto hero = static_cast<Hero*>(contact.getShapeB()->getBody()->getNode());
		if (bullet && bullet->getTag() == TAG_OF_BULLET_01 && hero && hero->getTag() == TAG_OF_KNIGHT)
		{
			if (!hero->getAlreadyDead())
			{
				hero->setColor(Color3B::RED);
				;
				hero->takeDamage(bullet);
				bullet->removeFromParent();

				if (hero->getAlreadyDead())
				{
					hero->initWithFile("Heroes/knight1.1Dead.png");
					hero->stopAllActions();
				}

			}
		}

		return true;
	};
	heroListener->onContactPreSolve = [&](PhysicsContact& contact, PhysicsContactPreSolve& solve)
	{

		return true;
	};
	heroListener->onContactPostSolve = [&](PhysicsContact& contact, const PhysicsContactPostSolve& solve)
	{

	};

	heroListener->onContactSeparate = [&](PhysicsContact& contact)
	{
		auto hero = (Hero*)contact.getShapeB()->getBody()->getNode();
		if (this->getKnightBeenSelected())
		{
			if (hero && (hero->getTag() == this->getKnight()->getTag()))
				hero->setColor(Color3B::WHITE);
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(heroListener, 1);

	// //////////////////////////////////////////////////////////////////////////////////////////
	this->listenerVec.pushBack(knightMoveListener);
	this->listenerVec.pushBack(monsterListener);
	this->listenerVec.pushBack(heroListener);
	/// ///////////////////////////////////////////////////////////////////////
	playMusic("sound/FightMapCaveBGM.mp3", true);
}

void Level03::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();

}

void Level03::onExitTransitionDidStart()
{
	Layer::onExitTransitionDidStart();

}

void Level03::onExit()//ע��������
{
	Layer::onExit();
	for (auto listener : listenerVec)
		Director::getInstance()->getEventDispatcher()->removeEventListener(listener);

}

void Level03::cleanup()
{
	Layer::cleanup();

}

void Level03::menuPauseCallback(cocos2d::Ref* pSender)//��ͣ��ť�Ļص�
{
	auto scene = Pause::createScene();
	Director::getInstance()->pushScene(scene);
	playSound("sound/ClickSound.mp3");
}


bool Level03::onTouchBegan(Touch* touch, Event* event)//���������ʿ����
{
	Vec2 position = convertTouchToNodeSpace(touch);
	if ((this->getKnightBeenSelected()) && (!this->getKnight()->getAlreadyDead()))//��ʿ��ѡ����û����
	{
		if ((this->getKnight()->getMP()) || ((!this->getKnight()->getMP()) && (!this->getWeapon()->getMPConsuming())))//�����δ��������Ѻ��굫����������
		{
			if (this->getKnight()->getAttackMode() <= HERO_MELEE_4)//���̹���
			{
				if (!attackTowardsTarget(this->getKnight()))
				{
					attackMelee(this->getKnight());
				}
			}
			else attackRemotely(position, this->getKnight());
			return false;
		}
	}
	return false;
}

void Level03::removeFromParent(Node* bullet)//ɾ���ӵ��Ļص�����
{
	bullet->removeFromParent();
}

void Level03::update(float delta)
{
	if (this->getKnightBeenSelected())
	{
		updateInformationArmor(this, this->getKnight());
		updateInformationHP(this, this->getKnight());
		this->getKnight()->updateSkill();
		updateSkillBox(this, this->getKnight());
		if ((!this->getKnight()->getAlreadyDead()))
		{
			knightMove();
		}
	}


}

void Level03::heroDieUpdate(float delta)
{
	if (this->getKnightBeenSelected() && this->getKnight()->getAlreadyDead())
	{
		auto deadScene = Dead::createScene();
		auto reScene = CCTransitionMoveInT::create(0.5f, deadScene);
		Director::getInstance()->replaceScene(reScene);
	}
}

void Level03::enemyAttackUpdate(float delta)
{
	int tileGid;
	float relativeX, relativeY, relativeR, searchX, searchY;
	float cosAlpha, sinAlpha;//�Ƕ�
	bool hit;
	hit = false;
	Vec2 hero;
	if ((this->getKnightBeenSelected()) && (!this->getKnight()->getAlreadyDead()))
	{
		hero = this->getKnight()->getPosition();
		for (const auto& monster : this->creepsVec)
		{
			if ((!monster->getAlreadyDead()) && (monster->getActive()))
			{
				if (monster->getAttackMode() >= ENEMY_REMOTE)
				{
					Vec2 enemy = monster->getPosition();
					if ((enemy.x >= hero.x - monster->getAttackRadius()) && (enemy.x <= hero.x + monster->getAttackRadius()) &&
						(enemy.y >= hero.y - monster->getAttackRadius()) && (enemy.y <= hero.y + monster->getAttackRadius()))
					{
						hit = false;
						relativeX = hero.x - enemy.x;
						relativeY = hero.y - enemy.y;
						relativeR = sqrt(relativeX * relativeX + relativeY * relativeY);
						cosAlpha = relativeX / relativeR;
						sinAlpha = relativeY / relativeR;
						searchX = enemy.x;
						searchY = enemy.y;
						relativeR = monster->getAttackRadius();
						while (relativeR > 0)
						{
							relativeR -= 20;
							searchX += 20 * cosAlpha;
							searchY += 20 * sinAlpha;
							int xxx = 0.5 * searchX / map->getTileSize().width;
							int yyy = ((map->getMapSize().height * map->getTileSize().height) - 0.5 * searchY) / map->getTileSize().height;

							Point posAfter = Point(xxx, yyy);

							tileGid = collidable->getTileGIDAt(posAfter);
							if (tileGid > 0)
							{
								Value prop = map->getPropertiesForGID(tileGid);

								ValueMap propValueMap = prop.asValueMap();

								std::string collision = propValueMap["Collidable"].asString();

								if (collision == "true")
								{
									hit = true;
									break;
								}
							}
						}
						this->setInAttackRange(true);
						auto enemyBullet = Bullet::create("Bullets/bullet1.png", monster->getAttack(), ATTACK_FREQUENCY_1, NORMAL);
						enemyBullet->setTag(TAG_OF_BULLET_01);

						auto Ebody = PhysicsBody::createBox(enemyBullet->getContentSize());
						Ebody->setCategoryBitmask(ENEMY_BULLET_1);//0010
						Ebody->setCollisionBitmask(0);
						Ebody->setContactTestBitmask(ENEMY_BULLET_2);
						enemyBullet->setPhysicsBody(Ebody);


						enemyBullet->setPosition(enemy);
						enemyBullet->runAction(Sequence::create(MoveTo::create(0.8f, Vec2(searchX, searchY)), CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, enemyBullet)), NULL));
						this->addChild(enemyBullet);

					}
				}
				else if (monster->getAttackMode() <= ENEMY_MELEE)
				{
					Vec2 enemy = monster->getPosition();
					if ((enemy.x >= hero.x - ENEMY_MELEE) && (enemy.x <= hero.x + ENEMY_MELEE) &&
						(enemy.y >= hero.y - ENEMY_MELEE) && (enemy.y <= hero.y + ENEMY_MELEE))
					{
						this->setInAttackRange(true);
						//this->setBeenAttacked(true);
						auto enemyBullet = Bullet::create("Bullets/bullet1.png", monster->getAttack(), ATTACK_FREQUENCY_1, NORMAL);
						enemyBullet->setTag(TAG_OF_BULLET_01);

						auto Ebody = PhysicsBody::createBox(enemyBullet->getContentSize());
						Ebody->setCategoryBitmask(ENEMY_BULLET_1);//0010
						Ebody->setCollisionBitmask(0);
						Ebody->setContactTestBitmask(ENEMY_BULLET_2);
						enemyBullet->setPhysicsBody(Ebody);


						enemyBullet->setPosition(enemy);
						enemyBullet->runAction(Sequence::create(MoveTo::create(0.4f, hero), CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, enemyBullet)), NULL));

						//this->setBeenAttacked(false);
						this->addChild(enemyBullet);
						enemyBullet->setVisible(false);
					}
				}
			}
		}
	}
}

void Level03::knightMove()//������update��ĺ�����ʵ����ʿ��ɫ���ƶ�
{
	Point playerPos = this->getKnight()->getPosition();
	Point anotherPos = this->getKnight()->getPosition();


	if (keys[EventKeyboard::KeyCode::KEY_D])
	{
		playerPos.x += map->getTileSize().width / 3;
		anotherPos.x += map->getTileSize().width / 8;

		this->getKnight()->runAction(FlipX::create(false));
		this->getWeapon()->runAction(FlipX::create(false));

	}
	if (keys[EventKeyboard::KeyCode::KEY_A])
	{
		playerPos.x -= map->getTileSize().width / 3;
		anotherPos.x -= map->getTileSize().width / 8;

		this->getKnight()->runAction(FlipX::create(true));
		this->getWeapon()->runAction(FlipX::create(true));

	}
	if (keys[EventKeyboard::KeyCode::KEY_S])
	{
		playerPos.y -= map->getTileSize().height / 3;
		anotherPos.y -= map->getTileSize().width / 8;

	}
	if (keys[EventKeyboard::KeyCode::KEY_W])
	{
		playerPos.y += map->getTileSize().height / 3;
		anotherPos.y += map->getTileSize().width / 8;

	}
	if (keys[EventKeyboard::KeyCode::KEY_Q])
	{
		collectProps();
		//buyProps();
	}
	if (keys[EventKeyboard::KeyCode::KEY_R])
	{
		Vec2 hero;
		if (this->getKnightBeenSelected())
		{
			hero = this->getKnight()->getPosition();
			for (int i = 0; i < weaponVec.size(); i++)
			{
				Vec2 weapon = weaponVec.at(i)->getPosition();
				if (weaponVec.at(i) && (weapon.x) && (weapon.y)
					&& (abs(hero.x - weapon.x) <= 60) && (abs(hero.y - weapon.y) <= 60) && (weaponVec.at(i) != this->getWeapon()))
				{

					this->setWeapon(weaponVec.at(i));
					this->setWeaponFilename(weaponVec.at(i)->getWeaponFilename());
					this->setBullet(bulletVec.at(i));
					this->setBulletFilename(bulletVec.at(i)->getBulletFilename());
					this->getKnight()->changeWeapon(weaponVec.at(i));
					this->getWeapon()->setPosition(hero.x, hero.y - 25);
					this->getBullet()->setScale(0);
					break;
				}

			}
		}

	}
	if (keys[EventKeyboard::KeyCode::KEY_E])
	{
		this->getKnight()->releaseSkill();
		updateSkillBox(this, this->getKnight());
		updateInformationMP(this, this->getKnight());
	}
	this->setPlayerPosition(playerPos, anotherPos);
	this->screenRoll(playerPos);

}

void Level03::attackMelee(Hero* hero)//û�й���Ŀ��ʱ���������
{

	this->getKnight()->consumeMP();
	float tempAngle = CCRANDOM_0_1() * 2 * PI;
	float x = this->getKnight()->getAttackRadius() * cos(tempAngle);
	float y = this->getKnight()->getAttackRadius() * sin(tempAngle);
	for (int i = 0; i < this->getBullet()->getAttackFrequency(); i++)
	{
		auto bullet = Bullet::create(this->getBulletFilename(), this->getBullet());
		Vec2 p = this->getWeapon()->getPosition();
		bullet->setTag(TAG_OF_BULLET_01);
		bullet->setPosition(p);
		bullet->setVisible(false);

		auto weaponcache = SpriteFrameCache::getInstance();
		// //
		std::string filename = this->getWeaponFilename();
		for (int j = 0; j < 4; j++)
			filename.pop_back();
		filename += "Attack.plist";
		weaponcache->addSpriteFramesWithFile(filename);
		// //
		Vector<SpriteFrame*>vec;
		char name[50] = { 0 };
		std::string file = this->getWeaponFilename();
		file.erase(0, 8);
		for (int i = 0; i < 6; i++)
		{
			sprintf(name, "%sAttack%04d", file.c_str(), i);
			vec.pushBack(weaponcache->getSpriteFrameByName(name));
		}
		Animation* weaponAnimation = Animation::createWithSpriteFrames(vec, 0.01f);
		weaponAnimation->setRestoreOriginalFrame(true);
		Animate* weaponAnimate = Animate::create(weaponAnimation);
		this->getWeapon()->runAction(weaponAnimate);
		//������ײ����
		auto body = PhysicsBody::createBox(bullet->getContentSize());
		body->setCategoryBitmask(MY_BULLET_1);//0010
		body->setCollisionBitmask(0);
		body->setContactTestBitmask(MY_BULLET_2);
		bullet->setPhysicsBody(body);
		this->addChild(bullet);
		bullet->runAction(Sequence::create(MoveBy::create(0.3f * (i + 1), Vec2(x, y)), CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, bullet)), NULL));
	}

	updateInformationMP(this, this->getKnight());

}

bool Level03::attackTowardsTarget(Hero* hero)
{

	int tileGid;
	float relativeX, relativeY, relativeR, searchX, searchY;
	float cosAlpha, sinAlpha;//�Ƕ�
	bool hit;
	hit = false;
	bool tag = false;

	Vec2 heroPos = this->getKnight()->getPosition();
	for (const auto monster : this->creepsVec)
	{
		Vec2 enemy = monster->getPosition();
		if (((!monster->getAlreadyDead()) && (enemy.x >= heroPos.x - _knight->getAttackRadius()) && (monster->getActive()) && (enemy.x <= heroPos.x + _knight->getAttackRadius()))
			&& ((enemy.y >= heroPos.y - _knight->getAttackRadius()) && (enemy.y <= heroPos.y + _knight->getAttackRadius())))
		{
			for (int i = 0; i < this->getBullet()->getAttackFrequency(); i++)//����Ƶ��
			{
				auto bullet = Bullet::create(this->getBulletFilename(), this->getBullet());
				Vec2 weapon = this->getWeapon()->getPosition();

				bullet->setVisible(false);
				auto weaponcache = SpriteFrameCache::getInstance();
				// //
				std::string filename = this->getWeaponFilename();
				for (int j = 0; j < 4; j++)
					filename.pop_back();
				filename += "Attack.plist";
				weaponcache->addSpriteFramesWithFile(filename);
				// //
				Vector<SpriteFrame*>vec;
				char name[50] = { 0 };
				std::string file = this->getWeaponFilename();
				file.erase(0, 8);
				for (int i = 0; i < 6; i++)
				{
					sprintf(name, "%sAttack%04d", file.c_str(), i);
					vec.pushBack(weaponcache->getSpriteFrameByName(name));
				}
				Animation* weaponAnimation = Animation::createWithSpriteFrames(vec, 0.005f);
				weaponAnimation->setRestoreOriginalFrame(true);
				Animate* weaponAnimate = Animate::create(weaponAnimation);
				this->getWeapon()->runAction(weaponAnimate);
				//������ײ����
				auto body = PhysicsBody::createBox(bullet->getContentSize());
				body->setCategoryBitmask(MY_BULLET_1);//0010
				body->setCollisionBitmask(0);
				body->setContactTestBitmask(MY_BULLET_2);
				bullet->setPhysicsBody(body);

				bullet->setTag(TAG_OF_BULLET_01);
				bullet->setPosition(weapon);
				this->addChild(bullet);

				bullet->runAction(Sequence::create(MoveTo::create(0.3f * (i + 1), enemy), CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, bullet)), NULL));
			}
			this->getKnight()->consumeMP();
			updateInformationMP(this, this->getKnight());
			tag = true;
			break;
		}
	}

	return tag;
}

void Level03::attackRemotely(Vec2 enemy, Hero* hero)
{
	int tileGid;
	float relativeX, relativeY, relativeR, searchX, searchY;
	float cosAlpha, sinAlpha;//�Ƕ�
	bool hit;
	hit = false;
	bool tag = false;
	for (int i = 0; i < this->getBullet()->getAttackFrequency(); i++)//����Ƶ��
	{
		Vec2 heroPos = hero->getPosition();
		auto bullet = Bullet::create(this->getBulletFilename(), this->getBullet());
		Vec2 weapon = this->getWeapon()->getPosition();

		auto body = PhysicsBody::createBox(bullet->getContentSize() * 2);
		body->setCategoryBitmask(MY_BULLET_1);//0010
		body->setCollisionBitmask(0);
		body->setContactTestBitmask(MY_BULLET_2);
		bullet->setPhysicsBody(body);

		bullet->setTag(TAG_OF_BULLET_01);
		bullet->setPosition(weapon);
		this->addChild(bullet);


		hit = false;
		relativeX = heroPos.x - enemy.x;
		relativeY = heroPos.y - enemy.y;
		relativeR = sqrt(relativeX * relativeX + relativeY * relativeY);
		cosAlpha = relativeX / relativeR;
		sinAlpha = relativeY / relativeR;
		searchX = heroPos.x;
		searchY = heroPos.y;
		if (relativeR != hero->getAttackRadius())
		{
			relativeR = hero->getAttackRadius();
		}
		while (relativeR > 0)
		{

			searchX -= 20 * cosAlpha;
			searchY -= 20 * sinAlpha;
			int xxx = 0.5 * searchX / map->getTileSize().width;
			int yyy = ((map->getMapSize().height * map->getTileSize().height) - 0.5 * searchY) / map->getTileSize().height;

			Point posAfter = Point(xxx, yyy);

			tileGid = collidable->getTileGIDAt(posAfter);
			if (tileGid > 0)
			{
				Value prop = map->getPropertiesForGID(tileGid);

				ValueMap propValueMap = prop.asValueMap();

				std::string collision = propValueMap["Collidable"].asString();

				if (collision == "true")
				{
					hit = true;
					break;
				}
			}
			relativeR -= 20;
		}
		if (hit == true)
		{
			bullet->runAction(Sequence::create(MoveTo::create(0.3f * (i + 1), Vec2(searchX, searchY)), CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, bullet)), NULL));
		}
		else
		{
			searchX -= 80 * cosAlpha;
			searchY -= 80 * sinAlpha;
			bullet->runAction(Sequence::create(MoveTo::create(0.3f * (i + 1), Vec2(searchX, searchY)), CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, bullet)), NULL));
		}
	}
	this->getKnight()->consumeMP();
	updateInformationMP(this, this->getKnight());
}

void Level03::enemyMoveUpdate(float delta)
{
	creepMove();
}

void Level03::creepMove()
{
	int xx, yy, tileGid;
	Point playerPos = this->getKnight()->getPosition();
	float relativeX, relativeY, relativeR, searchX, searchY;
	float cosAlpha, sinAlpha;//�Ƕ�
	bool hit;

	for (const auto& sprite : this->creepsVec)
	{
		if (!sprite->getAlreadyDead() && sprite->getActive())//�����һ��С��û�������ͻ�����Ӣ���ƶ�
		{
			//debuff
			if (sprite->getReleaseDebuff() == BURN)
			{
				sprite->setColor(Color3B::RED);

				int _HP = sprite->getHP();
				_HP -= 2;
				if (_HP <= 0)
				{
					sprite->setHP(0);
					sprite->setAlreadyDead(true);
					sprite->setAttackRadius(0);
				}
				else
				{
					sprite->setHP(_HP);
					sprite->setAlreadyDead(false);
				}
				if (sprite->getAlreadyDead())
				{
					creepDie(sprite);
				}
			}
			Point pos = sprite->getPosition();
			if (!this->getKnight()->getAlreadyDead())
			{
				if ((pos.x >= playerPos.x - sprite->getAttackRadius()) && (pos.x <= playerPos.x + sprite->getAttackRadius()))
				{
					if ((pos.y >= playerPos.y - sprite->getAttackRadius()) && (pos.y <= playerPos.y + sprite->getAttackRadius()))
					{
						hit = false;
						relativeX = playerPos.x - pos.x;
						relativeY = playerPos.y - pos.y;
						relativeR = sqrt(relativeX * relativeX + relativeY * relativeY);
						cosAlpha = relativeX / relativeR;
						sinAlpha = relativeY / relativeR;
						searchX = pos.x;
						searchY = pos.y;
						while (relativeR > 0)
						{

							searchX += 20 * cosAlpha;
							searchY += 20 * sinAlpha;
							int xxx = 0.5 * searchX / map->getTileSize().width;
							int yyy = ((map->getMapSize().height * map->getTileSize().height) - 0.5 * searchY) / map->getTileSize().height;

							Point posAfter = Point(xxx, yyy);

							tileGid = collidable->getTileGIDAt(posAfter);
							if (tileGid > 0)
							{
								Value prop = map->getPropertiesForGID(tileGid);

								ValueMap propValueMap = prop.asValueMap();

								std::string collision = propValueMap["Collidable"].asString();

								if (collision == "true")
								{
									hit = true;
									break;
								}
							}
							relativeR -= 20;
						}
						if (hit == true)
						{
							continue;
						}
						auto moveToKnight = MoveTo::create(1.5f, Vec2(playerPos.x, playerPos.y));
						sprite->runAction(moveToKnight);
						continue;
					}
				}
			}

			float tempAngle = CCRANDOM_0_1() * 2 * PI;
			float x, y;
			if (sprite->getReleaseDebuff() != FROST)
			{
				x = 32 * cos(tempAngle);
				y = 32 * sin(tempAngle);
			}
			else
			{
				sprite->setColor(Color3B::BLUE);
				x = 16 * cos(tempAngle);
				y = 16 * sin(tempAngle);
			}
			auto move = MoveBy::create(1.5f, Vec2(x, y));

			xx = pos.x + x;
			yy = pos.y + y;

			int xxx = 0.5 * xx / map->getTileSize().width;
			int yyy = ((map->getMapSize().height * map->getTileSize().height) - 0.5 * yy) / map->getTileSize().height;

			Point posAfter = Point(xxx, yyy);

			tileGid = collidable->getTileGIDAt(posAfter);
			if (tileGid > 0)
			{
				Value prop = map->getPropertiesForGID(tileGid);

				ValueMap propValueMap = prop.asValueMap();

				std::string collision = propValueMap["Collidable"].asString();

				if (collision == "true")
				{
					auto moveBack = MoveBy::create(0.5f, Vec2(-x, -y));
					sprite->runAction(moveBack);
					continue;
				}
			}
			else
			{
				sprite->runAction(move);
			}
		}
	}
}

void Level03::setPlayerPosition(Point position, Point anotherPos)
{
	//�����ص�����ת��Ϊ��Ƭ����
	Point tileCoord = this->transPoision(position);

	//�����Ƭ��GID
	const int tileGid = collidable->getTileGIDAt(tileCoord);

	if (tileGid > 0)
	{
		Value prop = map->getPropertiesForGID(tileGid);

		ValueMap propValueMap = prop.asValueMap();

		std::string collision = propValueMap["Collidable"].asString();
		std::string groundAttack = propValueMap["groundjian"].asString();

		std::string box0 = propValueMap["box0"].asString();
		std::string box1 = propValueMap["box1"].asString();
		std::string box2 = propValueMap["box2"].asString();
		std::string box3 = propValueMap["box3"].asString();
		std::string box4 = propValueMap["box4"].asString();

		std::string slow = propValueMap["slow"].asString();

		if (slow == "true") { //��ײ���ɹ�									


			this->getKnight()->setPosition(anotherPos);
			const Point pos = Point(anotherPos.x, anotherPos.y - 25);
			this->getWeapon()->setPosition(pos);
			return;
		}
		if (collision == "true") { //��ײ���ɹ�									

			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("empty.wav");

			return;

		}

		if (box0 == "true")
		{
			if (boxVec.at(0)->getOpen())
			{
				flag[0]++;
				if (flag[0] == 1)
				{
					insidePropsVec.at(0)->setVisible(true);
					insidePropsVec.at(1)->setVisible(true);
					insidePropsVec.at(2)->setVisible(true);
					boxVec.at(0)->initWithFile("Props/openBox.png");
				}
			}
		}
		if (box1 == "true") 
		{
			if (boxVec.at(1)->getOpen())
			{
				flag[1]++;
				if (flag[1] == 1)
				{
					boxVec.at(1)->initWithFile("Props/openBox.png");
					insidePropsVec.at(3)->setVisible(true);
					insidePropsVec.at(4)->setVisible(true);
					insidePropsVec.at(5)->setVisible(true);
				}
			}
		}
		if (box2 == "true")
		{
			flag[2]++;
			if (flag[2] == 1)
			{
				boxVec.at(2)->initWithFile("Props/openBox.png");
				insidePropsVec.at(6)->setVisible(true);
			}
		}
		if (box3 == "true")
		{
			if (boxVec.at(3)->getOpen())
			{
				flag[3]++;
				if (flag[3] == 1)
				{
					boxVec.at(3)->initWithFile("Props/openBox.png");
					insidePropsVec.at(7)->setVisible(true);
					insidePropsVec.at(8)->setVisible(true);
					insidePropsVec.at(9)->setVisible(true);
				}
			}
		}
		if (box4 == "true")
		{
			flag[4]++;
			if (flag[4] == 1) 
			{
				boxVec.at(4)->initWithFile("Props/openBox.png");
				insidePropsVec.at(10)->setVisible(true);
			}
		}
	}
	this->getKnight()->setPosition(position);
	const Point pos = Point(position.x, position.y - 25);
	this->getWeapon()->setPosition(pos);

	auto door = this->getChildByTag(TAG_OG_SAFEMAP_DOOR);
	if (door->getBoundingBox().containsPoint(this->getKnight()->getPosition()) && allClear)
		nextScene();//�������л�
	const Point posM = Point(position.x + 390, position.y + 380);

	smallK->setPosition(posM);
	smallMap->setPosition(posM);

}

Point Level03::transPoision(Point pos)
{
	int x = 0.5 * pos.x / map->getTileSize().width;
	int y = ((map->getMapSize().height * map->getTileSize().height) - 0.5 * pos.y) /

		map->getTileSize().height;

	return Point(x, y);
}


void Level03::screenRoll(Point position)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//��Ļ���ĵ�

	Point pointA = Point(visibleSize.width / 2, visibleSize.height / 2);

	Point pointB = position;
	//position

	//��ͼ�ƶ�ƫ����

	Point offset = (pointA - pointB);

	this->setPosition(offset);

	Point point0 = smallMap->getPosition();

	Point offset0 = (Vec2(-78, -65));

	smallK->setPosition(-0.025 * offset + point0 + offset0);


}


void Level03::armorRecoverUpdate(float delta)
{
	if (this->getKnightBeenSelected() && (!this->getKnight()->getAlreadyDead()))
		updateHeroArmor(this->getKnight());
}

void Level03::nextScene()
{
	auto scene = Level04::createScene();
	////Ԥ����
	scene->removeChildByTag(TAG_OF_LEVEL_04);
	//
	auto stage = Level04::create();

	auto knight = Knight::create(this->getKnightFilename(), this->getKnight());
	auto weapon = Weapon::create(this->getWeaponFilename(), this->getWeapon());
	auto bullet = Bullet::create(this->getBulletFilename(), this->getBullet());

	knight->setPosition(Vec2(640, 480));
	weapon->setPosition(Vec2(640, 455));

	knight->setTag(TAG_OF_KNIGHT);
	weapon->setTag(TAG_OF_KNIGHT_INITIAL_WEAPON);;

	//������ײ����
	auto heroBody = PhysicsBody::createBox(knight->getContentSize());
	heroBody->setCategoryBitmask(MY_HERO_1);
	heroBody->setCollisionBitmask(0);
	heroBody->setContactTestBitmask(MY_HERO_2);
	knight->setPhysicsBody(heroBody);

	auto weaponBody = PhysicsBody::createBox(weapon->getContentSize());
	weaponBody->setCategoryBitmask(WEAPON_1);
	weaponBody->setCollisionBitmask(0);
	weaponBody->setContactTestBitmask(WEAPON_2);
	weapon->setPhysicsBody(weaponBody);
	////��ɫ�����dsd
	stage->addChild(knight);
	stage->addChild(weapon);
	stage->setKnight(knight);
	stage->setWeapon(weapon);
	stage->setKnightFilename(knight->getActorFilename());
	stage->setWeaponFilename(weapon->getWeaponFilename());
	stage->weaponVec.pushBack(weapon);
	stage->bulletVec.pushBack(bullet);

		bullet->setVisible(0);
		stage->addChild(bullet);
		stage->setBullet(bullet);
		stage->setBulletFilename(bullet->getBulletFilename());
	
		//���ô��Ĺؿ���
		int num = knight->getLevelNum() + 1;
		knight->setLevelNum(num);
		successLevelNum = knight->getLevelNum();

	if (this->getKnightBeenSelected())
	{
		stage->setKnightBeenSelected(true);
	}
	// ////////////////////////

	scene->addChild(stage, 0);

	//////////����InformationBox
	createInformationBox(stage, knight);
	createSkillBox(stage, knight);
	createGoldBox(stage, knight);

	auto reScene = TransitionProgressOutIn::create(0.5f, scene);
	Director::getInstance()->replaceScene(reScene);
}

void Level03::collectProps()
{
	if (!this->getKnight()->getAlreadyDead())
	{
		Vec2 position = this->getKnight()->getPosition();
		for (auto props : propsVec)
		{
			if (props->isInRange(position))
			{
				/*props->runAction(MoveBy::create(0.3f, position));*/
				props->setVisible(false);
				props->makeEffect(this, this->getKnight());
				updateGoldBox(this, this->getKnight());
			}
		}
	}
}

void Level03::initProps()
{
	//��һ������0
	//��ƿ
	auto drugMP01 = Props::create("Props/healMagic.png", PROPS_DRUG_MP, boxPositionVec[0].x, boxPositionVec[0].y, 50);
	drugMP01->setPosition(boxPositionVec[0].x + 50, boxPositionVec[0].y);
	drugMP01->setTag(TAG_OF_PROPS_MP);
	propsVec.pushBack(drugMP01);
	insidePropsVec.pushBack(drugMP01);
	drugMP01->setVisible(false);
	addChild(drugMP01, 2);

	auto drugMP11 = Props::create("Props/healMagic.png", PROPS_DRUG_MP, boxPositionVec[0].x, boxPositionVec[0].y, 50);
	drugMP11->setPosition(boxPositionVec[0].x -50, boxPositionVec[0].y);
	drugMP11->setTag(TAG_OF_PROPS_MP);
	propsVec.pushBack(drugMP11);
	insidePropsVec.pushBack(drugMP11);
	drugMP11->setVisible(false);
	addChild(drugMP11, 2);

	//���
	auto gold01 = Props::create("Props/gold.png", PROPS_GOLD, boxPositionVec[0].x, boxPositionVec[0].y, 50);
	gold01->setPosition(boxPositionVec[0]);
	propsVec.pushBack(gold01);
	insidePropsVec.pushBack(gold01);
	gold01->setVisible(false);
	addChild(gold01, 2);

	//�ڶ�������1
	auto drugMP02 = Props::create("Props/healMagic.png", PROPS_DRUG_MP, boxPositionVec[1].x, boxPositionVec[1].y, 50);
	drugMP02->setPosition(boxPositionVec[1].x + 50, boxPositionVec[1].y);
	drugMP02->setTag(TAG_OF_PROPS_MP);
	propsVec.pushBack(drugMP02);
	insidePropsVec.pushBack(drugMP02);
	drugMP02->setVisible(false);
	addChild(drugMP02, 2);

	auto gold02 = Props::create("Props/gold.png", PROPS_GOLD, boxPositionVec[1].x, boxPositionVec[1].y, 50);
	gold02->setPosition(boxPositionVec[1]);
	propsVec.pushBack(gold02);
	insidePropsVec.pushBack(gold02);
	gold02->setVisible(false);
	addChild(gold02, 2);

	auto drugHP02 = Props::create("Props/healBlood.png", PROPS_DRUG_HP, boxPositionVec[1].x, boxPositionVec[1].y, 50);
	drugHP02->setPosition(boxPositionVec[1].x-50,boxPositionVec[1].y);
	drugHP02->setTag(TAG_OF_PROPS_HP);
	propsVec.pushBack(drugHP02);
	insidePropsVec.pushBack(drugHP02);
	drugHP02->setVisible(false);
	addChild(drugHP02, 2);

	//����������2
	auto drugHP = Props::create("Props/healBlood.png", PROPS_DRUG_HP, boxPositionVec[2].x, boxPositionVec[2].y, 50);
	drugHP->setPosition(boxPositionVec[2]);
	drugHP->setTag(TAG_OF_PROPS_HP);
	propsVec.pushBack(drugHP);
	insidePropsVec.pushBack(drugHP);
	drugHP->setVisible(false);
	addChild(drugHP, 2);

	//���ĸ�����--3

	weaponVec.at(0)->setPosition(boxPositionVec[3]);
	insidePropsVec.pushBack(weaponVec.at(0));
	this->addChild(weaponVec.at(0), 2);
	this->addChild(bulletVec.at(0), 2);
	weaponVec.at(0)->setVisible(false);
	bulletVec.at(0)->setVisible(false);

	auto drugMP04 = Props::create("Props/healMagic.png", PROPS_DRUG_MP, boxPositionVec[3].x, boxPositionVec[3].y, 50);
	drugMP04->setPosition(boxPositionVec[3].x + 50, boxPositionVec[3].y);
	drugMP04->setTag(TAG_OF_PROPS_MP);
	propsVec.pushBack(drugMP04);
	insidePropsVec.pushBack(drugMP04);
	drugMP04->setVisible(false);
	addChild(drugMP04, 2);

	auto gold04 = Props::create("Props/gold.png", PROPS_GOLD, boxPositionVec[3].x, boxPositionVec[3].y, 50);
	gold04->setPosition(boxPositionVec[3].x -50, boxPositionVec[3].y);
	propsVec.pushBack(gold04);
	insidePropsVec.pushBack(gold04);
	gold04->setVisible(false);
	addChild(gold04, 2);

	//���������--�������䣩4

	weaponVec.at(1)->setPosition(boxPositionVec[4]);
	insidePropsVec.pushBack(weaponVec.at(1));
	this->addChild(weaponVec.at(1), 2);
	this->addChild(bulletVec.at(1), 2);
	weaponVec.at(1)->setVisible(false);
	bulletVec.at(1)->setVisible(false);
}



void Level03::groundAttackUpdate(float delta)
{
	Point tileCoord = this->transPoision(this->getKnight()->getPosition());

	//�����Ƭ��GID
	const int tileGid = collidable->getTileGIDAt(tileCoord);

	if (tileGid > 0)
	{
		Value prop = map->getPropertiesForGID(tileGid);

		ValueMap propValueMap = prop.asValueMap();

		//std::string collision = propValueMap["Collidable"].asString();

		std::string groundAttack = propValueMap["groundjian"].asString();

		if (groundAttack == "true")
		{
			auto knight = this->getKnight();
			colorKnight = knight->getColor();
			knight->setColor(Color3B::RED);

			int armor = knight->getArmor() - GROUNDATTACK_1;
			knight->setArmor(armor);
			if (knight->getArmor() < 0)
			{
				int hp = abs(knight->getArmor());
				knight->setArmor(0);
				knight->setHP(knight->getHP() - hp);
				if (knight->getHP() <= 0)
				{
					knight->setHP(0);
					knight->setAlreadyDead(true);
					knight->setAttackRadius(0);
				}
				else
					knight->setAlreadyDead(false);
			}
			this->schedule(schedule_selector(Level03::returnColor), 0, 1, 0.1f);

		}//�ش�



	}
}

void Level03::returnColor(float dt)
{
	auto knight = this->getKnight();
	knight->setColor(colorKnight);
}

void Level03::initWeapon()
{

	//����1������
	Weapon* weaponBasketball = Weapon::create("Weapons/weaponBasketball.png", HERO_ATTACK_LOW, CONSUMPTION_2, HERO_REMOTE, NORMAL);
	Bullet* bulletBasketball = Bullet::create("Weapons/weaponBasketball.png", HERO_ATTACK_LOW, ATTACK_FREQUENCY_3, NORMAL);
	weaponVec.pushBack(weaponBasketball);
	bulletVec.pushBack(bulletBasketball);


	//����2���η౦��������
	Weapon* weaponToiletPump = Weapon::create("Weapons/weaponToiletPump.png", HERO_ATTACK_HIGH, CONSUMPTION_3, HERO_REMOTE_2, BURN);
	Bullet* bulletToiletPump = Bullet::create("Bullets/bulletShit.png", HERO_ATTACK_HIGH, ATTACK_FREQUENCY_1, BURN);
	weaponVec.pushBack(weaponToiletPump);
	bulletVec.pushBack(bulletToiletPump);

	//����3:��ǹ
	Weapon* weaponRifle = Weapon::create("Weapons/weaponGun2.png", HERO_ATTACK_MEDIUM, CONSUMPTION_4, HERO_REMOTE_3, NORMAL);
	Bullet* bulletRifle = Bullet::create("Bullets/bullet1.png", HERO_ATTACK_MEDIUM, ATTACK_FREQUENCY_5, NORMAL);
	weaponVec.pushBack(weaponRifle);
	bulletVec.pushBack(bulletRifle);

	//����4����
	Weapon* weaponFish = Weapon::create("Weapons/weaponFish.png", HERO_ATTACK_LOW, CONSUMPTION_1, HERO_REMOTE_1, FROST);
	Bullet* bulletFish = Bullet::create("Bullets/bullet5.png", HERO_ATTACK_LOW, ATTACK_FREQUENCY_1, FROST);
	weaponVec.pushBack(weaponFish);
	bulletVec.pushBack(bulletFish);

	//����5����
	Weapon* weaponFork = Weapon::create("Weapons/weaponFork.png", HERO_ATTACK_MEDIUM, CONSUMPTION_0, HERO_MELEE_2, NORMAL);
	Bullet* bulletFork = Bullet::create("Bullets/bullet4.png", HERO_ATTACK_MEDIUM, ATTACK_FREQUENCY_1, NORMAL);
	weaponVec.pushBack(weaponFork);
	bulletVec.pushBack(bulletFork);

	//����6����

	Weapon* weaponKnife = Weapon::create("Weapons/weaponKnife2.png", HERO_ATTACK_HIGH, CONSUMPTION_1, HERO_MELEE_4, NORMAL);
	Bullet* bulletKnife = Bullet::create("Bullets/bullet4.png", HERO_ATTACK_HIGH, ATTACK_FREQUENCY_3, NORMAL);
	weaponVec.pushBack(weaponKnife);
	bulletVec.pushBack(bulletKnife);
}