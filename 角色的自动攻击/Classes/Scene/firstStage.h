
//���ǰ�ȫ��ͼ
#pragma once
#ifndef __FIRST_STAGE_H__
#define __FIRST_STAGE_H__

#include"Scene/startScene.h"
#include"cocos2d.h"
#include"Hero/Knight.h"
#include"Constant/Constant.h"
#include"Equipment/Bullet.h"


//���ԣ�
#include"Actor/Creep.h"

USING_NS_CC;

class firstStage : public cocos2d::Layer
{
	CC_SYNTHESIZE(bool, _knightBeenSelected, KnightBeenSelected);//��ɫ��ʿ�Ƿ�ѡ��
	CC_SYNTHESIZE(bool, _inAttackRange, InAttackRange);//�жϵ����Ƿ��ڹ�����Χ��
public:
	void update(float delta);

	static cocos2d::Scene* createScene();//��������
	virtual bool init();//��ʼ��

	virtual void onEnter();//ע�������
	virtual void onExit();//ע��������
	bool chooseKnightTouchBegan(Touch* touch, Event* event);//ѡ��Ӣ��-��ʿ����ʼ��
	void chooseKnightTouchEnded(Touch* touch, Event* event);//ѡ��Ӣ��-��ʿ��������

	
	//bool shootTouchBegan(Touch* touch, Event* event);//�������꿪ʼ�����
	//void shootTouchEnded(Touch* touch, Event* event);//����������������
	bool onTouchBegan(Touch* touch, Event* event);
	void removeFromParent( Node* m);
	
	

	CREATE_FUNC(firstStage);

private:
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;
};


#endif // __FIRST_STAGE_H__

