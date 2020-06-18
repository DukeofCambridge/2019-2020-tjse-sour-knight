#include"Function/CommonFunction.h"


//1.informationBox�Ľ��������Ͻ������ۣ�
//�������ܣ�layer:��Ҫ����һ��Ϣ�������ĸ������У�hero:����˭����Ϣ
 void createInformationBox(Layer* layer, const Hero* hero)
{
	 Scene* scene=static_cast<Scene*>(layer->getParent());
	auto informationBox = Sprite::create("Infos/informationBox.png");
	informationBox->setPosition(Vec2(150, 890));
	int maxHP =hero->getMaxHP(), maxArmor = hero->getMaxArmor(), maxMP = hero->getMaxMP();

	//���ý������ٷֱ�
	float mp = hero->getMP();
	float percentMP = mp / maxMP * 100;

	float hp = hero->getHP();
	float percentHP = hp / maxHP * 100;

	float Armor = hero->getArmor();
	float percentArmor = Armor / maxArmor * 100;

	//HP
	auto HP = LoadingBar::create("Infos/HP.png");
	HP->setPosition(Vec2(167, 925));
	HP->setDirection(LoadingBar::Direction::LEFT);
	HP->setPercent(percentHP);
	HP->setTag(TAG_OF_HP_BAR);

	auto labelHP = Label::create("labelHP", "fonts/arial", 30);
	labelHP->setString(StringUtils::format("%d/%d", hero->getHP(), maxHP));
	labelHP->setPosition(Vec2(167, 925));
	labelHP->setColor(Color3B(255, 255, 0));
	labelHP->setTag(TAG_OF_LABEL_HP);

	//armor
	auto armor = LoadingBar::create("Infos/Armor.png");
	armor->setPosition(Vec2(167, 894));
	armor->setDirection(LoadingBar::Direction::LEFT);
	armor->setPercent(percentArmor);
	armor->setTag(TAG_OF_ARMOR_BAR);

	auto labelArmor = Label::create("labelArmor", "fonts/arial", 30);
	labelArmor->setString(StringUtils::format("%d/%d", hero->getArmor(), maxArmor));
	labelArmor->setPosition(Vec2(167, 894));
	labelArmor->setColor(Color3B(255, 255, 0));
	labelArmor->setTag(TAG_OF_LABEL_ARMOR);
	//MP
	auto MP = LoadingBar::create("Infos/MP.png");
	MP->setPosition(Vec2(167, 860));
	MP->setDirection(LoadingBar::Direction::LEFT);
	MP->setPercent(percentMP);
	MP->setTag(TAG_OF_MP_BAR);

	auto labelMP = Label::create("labelMP", "fonts/arial", 30);
	labelMP->setString(StringUtils::format("%d/%d", hero->getMP(), maxMP));
	labelMP->setPosition(Vec2(167, 860));
	labelMP->setColor(Color3B(255, 255, 0));
	labelMP->setTag(TAG_OF_LABEL_MP);

	scene->addChild(informationBox,1);
	scene->addChild(HP,1);
	scene->addChild(labelHP,1);
	scene->addChild(MP,1);
	scene->addChild(labelMP,1);
	scene->addChild(armor,1);
	scene->addChild(labelArmor,1);
}

//2.informationBox�ĸ��£���ֵ�ĸ��£�
//�������ܣ�layer:��Ҫ����һ��Ϣ�������ĸ������У�hero:����˭����Ϣ

 void updateInformationMP(Layer* layer, Hero* hero)
 {
	 Scene* scene = static_cast<Scene*>(layer->getParent());
	 hero->consumeMP();
	 scene->removeChildByTag(TAG_OF_MP_BAR);
	 scene->removeChildByTag(TAG_OF_LABEL_MP);

	 int  maxMP =hero->getMaxMP();
	 float mp = hero->getMP();
	 float percent = mp / maxMP * 100;

	 //MP
	 auto MP = LoadingBar::create("Infos/MP.png");
	 MP->setPosition(Vec2(167, 860));
	 MP->setDirection(LoadingBar::Direction::LEFT);
	 MP->setPercent(percent);
	 MP->setTag(TAG_OF_MP_BAR);

	 auto labelMP = Label::create("labelMP", "fonts/arial", 30);
	 labelMP->setString(StringUtils::format("%d/%d", hero->getMP(), maxMP));
	 labelMP->setPosition(Vec2(167, 860));
	 labelMP->setColor(Color3B(255, 255, 0));
	 labelMP->setTag(TAG_OF_LABEL_MP);

	 scene->addChild(MP,1);
	 scene->addChild(labelMP,1);
 }
	
//3.informationBox�ĸ��£����׵ĸ��£�
 void updateInformationArmor(Layer* layer, Hero* hero)
 {
	 Scene* scene = static_cast<Scene*>(layer->getParent());

	 scene->removeChildByTag(TAG_OF_ARMOR_BAR);
	 scene->removeChildByTag(TAG_OF_LABEL_ARMOR);

	 int  maxArmor = hero->getMaxArmor();
	 float armor = hero->getArmor();
	 if (armor <= 0)
		 armor = 0;
	 float percent = armor / maxArmor * 100;

	 
	 auto Armor = LoadingBar::create("Infos/Armor.png");
	 Armor->setPosition(Vec2(167, 894));
	 Armor->setDirection(LoadingBar::Direction::LEFT);
	 Armor->setPercent(percent);
	 Armor->setTag(TAG_OF_ARMOR_BAR);

	 auto labelArmor = Label::create("labelArmor", "fonts/arial", 30);
	 labelArmor->setString(StringUtils::format("%d/%d", hero->getArmor(), maxArmor));
	 labelArmor->setPosition(Vec2(167, 894));
	 labelArmor->setColor(Color3B(255, 255, 0));
	 labelArmor->setTag(TAG_OF_LABEL_ARMOR);

	 scene->addChild(Armor, 1);
	 scene->addChild(labelArmor, 1);
 }

 //4.informationBoc�ĸ��£�Ѫ���ĸ��£�
 void updateInformationHP(Layer* layer, Hero* hero)
 {
	 Scene* scene = static_cast<Scene*>(layer->getParent());

	 scene->removeChildByTag(TAG_OF_HP_BAR);
	 scene->removeChildByTag(TAG_OF_LABEL_HP);

	 int  maxHP = hero->getMaxHP();
	 float hp = hero->getHP();
	 if (hp <= 0)
		 hp = 0;
	 float percent = hp / maxHP * 100;


	 auto HP = LoadingBar::create("Infos/HP.png");
	 HP->setPosition(Vec2(167, 925));
	 HP->setDirection(LoadingBar::Direction::LEFT);
	 HP->setPercent(percent);
	 HP->setTag(TAG_OF_HP_BAR);

	 auto labelHP = Label::create("labelHP", "fonts/arial", 30);
	 labelHP->setString(StringUtils::format("%d/%d", hero->getHP(), maxHP));
	 labelHP->setPosition(Vec2(167, 925));
	 labelHP->setColor(Color3B(255, 255, 0));
	 labelHP->setTag(TAG_OF_LABEL_HP);

	 scene->addChild(HP, 1);
	 scene->addChild(labelHP, 1);
 }

 //5.Ӣ�ۻ��׵�����
 void updateHeroArmor(Hero* hero)
 {
	 if (hero->getArmor() < hero->getMaxArmor())
	 {
		 int armor = hero->getArmor();
		 armor++;
		 hero->setArmor(armor);
	 }
}