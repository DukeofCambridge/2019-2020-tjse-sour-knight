#include"Scene/chooseKnightScene.h"

Scene* chooseKnightScene::createScene()
{
	return chooseKnightScene::create();
}

bool chooseKnightScene::init()
{
	if (!Scene::init())
		return false;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto bg = Sprite::create("Backgrounds/chooseKnightScene.png");
	bg->setPosition((Vec2(visibleSize.width / 2, visibleSize.height / 2)));
	this->addChild(bg);


	knight= Sprite::create("Heroes/choosingKnight.png");
	knight->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(knight);

	auto knightInfo = Sprite::create("Infos/infoKnight.png");
	knightInfo->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 350));
	this->addChild(knightInfo);

	auto backMenuItem = MenuItemImage::create("Buttons/buttonExit.png", "Buttons/buttonExitClicked.png", CC_CALLBACK_1(chooseKnightScene::backMenu, this));
	backMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(120, 100)));
	auto goMenuItem = MenuItemImage::create("Buttons/buttonContinue.png", "Buttons/buttonContinueClicked.png", CC_CALLBACK_1(chooseKnightScene::goMenu, this));
	goMenuItem->setPosition(visibleSize.width / 2, 100);
	Menu* mn = Menu::create(backMenuItem, goMenuItem, NULL);
	mn->setPosition(Vec2::ZERO);
	this->addChild(mn);
	
	return true;

}

void chooseKnightScene::backMenu(Ref* pSender)
{
	auto sc = firstStage::createScene();
	
	auto reScene = TransitionPageTurn::create(0.5f, sc,true);
	Director::getInstance()->replaceScene(reScene);
	playSound("sound/ClickSound.mp3");
}


void chooseKnightScene::goMenu(Ref *pSender)
{
	auto sc = firstStage::createScene();
//Ԥ����	
	sc->removeChildByTag(TAG_OF_FIRST_STAGE_LAYER);
	
	auto stage = firstStage::create();
	stage->setKnightBeenSelected(true);
	stage->removeChildByTag(TAG_OF_KNIGHT);
// /
	//�������������
	auto weapon = Weapon::create("Weapons/weaponGun.png", 3, 1, HERO_REMOTE, NORMAL);
	auto knight = Knight::create("Heroes/knight1.1.png", weapon);
	log("%d", knight->getAlreadyDead());
	knight->setPosition(Vec2(640, 480));
	knight->setTag(TAG_OF_KNIGHT);
	log("%f", knight->getPosition().x);
	log("%f", knight->getPosition().y);

	weapon->setPosition(Vec2(640, 455));
	
	weapon->setTag(TAG_OF_KNIGHT_INITIAL_WEAPON);
	///������ײ����
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

	
// //��ɫ�����
	stage->addChild(knight);
	stage->addChild(weapon);
	sc->addChild(stage,0);
	stage->setKnight(knight);
	stage->setWeapon(weapon);

	////////����InformationBox
	createInformationBox(stage, knight);

	log("%f", weapon->getPosition().x);
	log("%f", weapon->getPosition().y);

// //////�����л�
	auto reScene = TransitionProgressOutIn::create(0.5f, sc);
	Director::getInstance()->replaceScene(reScene);
	playSound("sound/ClickSound.mp3");


}

