#pragma once


#ifndef __HELLOWORLDF4_SCENE_H__

#define __HELLOWORLDF4_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include"Scene/firstStage.h"
#include "Hero/Knight.h"
#include"Constant/Constant.h"
#include "Equipment/Bullet.h"
#include"Equipment/Weapon.h"
#include"Settings/SoundAndMusic.h"
#include"Settings/pauseControl.h"
#include"Settings/CreateDoor.h"
#include"Function/CommonFunction.h"
#include"Actor/Creep.h"
#include"Scene/DeadScene.h"


using namespace CocosDenshion;
USING_NS_CC;

class Level04 : public cocos2d::Layer

{
	cocos2d::TMXTiledMap* map;

	cocos2d::TMXLayer* collidable;

	cocos2d::Sprite* smallMap;

	cocos2d::Sprite* smallK;

	void bossMoveUpdate(float delta);//����boss���ƶ�
	void bossAttackUpdate(float dt);
	cocos2d::Vector<Creep*>bossVec;//boss

	CC_SYNTHESIZE(Knight*, _knight, Knight);//��ɫ--��ʿ
	CC_SYNTHESIZE(Weapon*, _weapon, Weapon);//����
	CC_SYNTHESIZE(Bullet*, _bullet, Bullet);//�ӵ�
	CC_SYNTHESIZE(std::string, knightFilename, KnightFilename);//��ʿ���ļ���
	CC_SYNTHESIZE(std::string, weaponFilename, WeaponFilename);//�������ļ���
	CC_SYNTHESIZE(std::string, bulletFilename, BulletFilename);//�ӵ����ļ���
	CC_SYNTHESIZE(bool, _knightBeenSelected, KnightBeenSelected);//��ɫ��ʿ�Ƿ�ѡ��
	CC_SYNTHESIZE(bool, _inAttackRange, InAttackRange);//�жϵ����Ƿ��ڹ�����Χ��

// ///////////////////////////////////////////////////////
public:
	//update��غ���
	void update(float delta);
	void enemyMoveUpdate(float delta);//���˵��ƶ�
	void enemyAttackUpdate(float dt);//���˵Ĺ���
	void armorRecoverUpdate(float dt);//���׵Ļָ�
	void heroDieUpdate(float dt);//Ӣ�۽�ɫ�������볡�����л�
	void groundAttackUpdate(float dt);//�ش�
	void returnColor(float dt);
	Color3B colorKnight;
	//���ﶯ����غ���
	void knightMove();//��ʿ��ɫ���ƶ�
	void creepMove();//С�ֵ��ƶ�
	void creepDie(Creep* creep);//С�ֵ�����
	void createMonster(char arr[5][4], const std::string& location, int num);//С�ֵĴ���
	void attackMelee(Hero* hero);//��Ŀ��ʱ��ս����
	bool attackTowardsTarget(Hero* hero);//��Ŀ��ʱ��ս����
	void attackRemotely(Vec2 vec, Hero* hero);//Զ�̹���

	void setPlayerPosition(cocos2d::Point position);
	cocos2d::Point transPoision(cocos2d::Point position);
	void screenRoll(cocos2d::Point position);

	//��ʼ����غ���
	static cocos2d::Scene* createScene();//��������
	virtual bool init();//��ʼ��
	void initWeapon();//��ʼ��

	virtual void onEnter();//ע�������
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();//ע��������
	virtual void onExitTransitionDidStart();
	virtual void cleanup();
	//�̵���غ���
	void initShop();
	void buyProps();
	//������غ���
	void collectProps();
	void initProps();

	void menuPauseCallback(cocos2d::Ref* pSender);
	bool onTouchBegan(Touch* touch, Event* event);
	void removeFromParent(Node* m);
	//�л�����һ��
	void nextScene();

	CREATE_FUNC(Level04);
	cocos2d::Vector<Weapon*>weaponVec;//������--����
	cocos2d::Vector<Bullet*>bulletVec;//������--�ӵ�
private:
	int buyTimes;
	Vector<Props*>propsOnSaleVec;//�̵��������
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;//��������
	cocos2d::Vector<Creep*> creepsVec;//С������
	cocos2d::Vector<EventListener*>listenerVec;//����������
	Vector<Props*>propsVec;//��������


	bool creepDieArr[15];//�����Ƿ���
	int littleMapClear[4];//С���ڹ�����ȥ������
	int littleMapWave[4];//С���Ƿ��������
	int deadCreeps;//�����Ĺ�������
	bool allClear;//���ȫ��
};
#endif // __HELLOWORLD4_SCENE_H__
