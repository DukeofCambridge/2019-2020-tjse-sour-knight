#pragma once
#ifndef BUFF_H_
#define BUFF_H_

#include <iostream>
#include"cocos2d.h";
USING_NS_CC;

const enum EBuff
{
	ICE_SHIELD,      //����
	POISON_SHIELD,    //����
	FIRE_SHIELD,      //���
	ADD_ARMOR,       //��������ֵ
	ADD_HP,          //����Ѫ��
	ADD_MP           //��������
};

//Buff��
class Buff :public Sprite
{
	CC_SYNTHESIZE(int, _addArmor, AddArmor);//���ӻ���ֵ
	CC_SYNTHESIZE(int, _addHP, AddHP);//��������ֵ
	CC_SYNTHESIZE(int, _addMP, AddMP);//��������ֵ
	CC_SYNTHESIZE(bool, _iceShield, IceShield);
	CC_SYNTHESIZE(bool, _poisonShield, PoisonShield);
	CC_SYNTHESIZE(bool, _fireShield, FireShield);

public:
	virtual bool init(const std::string& filename,EBuff Typebuff);
	static Buff* create(const std::string& filename,EBuff Typebuff);
};
#endif // !BUFF_H_

