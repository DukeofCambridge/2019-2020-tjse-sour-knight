#pragma once

#ifndef __HELLOWORLDF2_SCENE_H__

#define __HELLOWORLDF2_SCENE_H__

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

class Level02 : public cocos2d::Layer

{
	cocos2d::TMXTiledMap* map;

	cocos2d::TMXLayer* collidable;

	CC_SYNTHESIZE(Knight*, _knight, Knight);//��ɫ--��ʿ
	CC_SYNTHESIZE(Weapon*, _weapon, Weapon);//����
	CC_SYNTHESIZE(Bullet*, _bullet, Bullet);//�ӵ�
	CC_SYNTHESIZE(bool, _knightBeenSelected, KnightBeenSelected);//��ɫ��ʿ�Ƿ�ѡ��
	CC_SYNTHESIZE(bool, _inAttackRange, InAttackRange);//�жϵ����Ƿ��ڹ�����Χ��
// //////////////////////////////////////////////////////////
	//CC_SYNTHESIZE(bool, _beenAttacked, BeenAttacked);//�ж��Ƿ񱻹���
// ///////////////////////////////////////////////////////
public:
	//update��غ���
	void update(float delta);
	void enemyMoveUpdate(float delta);//���˵��ƶ�
	void enemyAttackUpdate(float dt);//���˵Ĺ���
	void armorRecoverUpdate(float dt);//���׵Ļָ�
	void heroDieUpdate(float dt);//Ӣ�۽�ɫ�������볡�����л�

	//���ﶯ����غ���
	void knightMove();//��ʿ��ɫ���ƶ�
	void creepMove();//С�ֵ��ƶ�
	void creepDie(Creep* creep);//С�ֵ�����
	void createMonster(char arr[5][4], const std::string& location, int num);//С�ֵĴ���
	void attackRandomly(Bullet* bullet);//��Ŀ��ʱ����
	bool attackTawordsTarget(Bullet* bullet);//��Ŀ��ʱ����

	void setPlayerPosition(cocos2d::Point position);
	cocos2d::Point transPoision(cocos2d::Point position);
	void screenRoll(cocos2d::Point position);

	//��ʼ����غ���
	static cocos2d::Scene* createScene();//��������
	virtual bool init();//��ʼ��


	virtual void onEnter();//ע�������
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();//ע��������
	virtual void onExitTransitionDidStart();
	virtual void cleanup();

	void menuPauseCallback(cocos2d::Ref* pSender);

	bool onTouchBegan(Touch* touch, Event* event);
	void removeFromParent(Node* m);


	CREATE_FUNC(Level02);

private:
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;//��������
	cocos2d::Vector<Creep*> creepsVec;//С������
	cocos2d::Vector<EventListener*>listenerVec;//����������
	bool creepDieArr[15];//�����Ƿ���
	int littleMapClear[3];//С���ڹ�����ȥ������
	int littleMapWave[3];//С���Ƿ��������

};
#endif // __HELLOWORLD2_SCENE_H__

