#pragma once

#ifndef _WEAPON_H_
#define _WEAPON_H_

#include"cocos2d.h"
#include"Constant/Constant.h"
#include"Component/Debuff.h"

USING_NS_CC;

//˵�����ڽ���������ʱ��include"Equipment/Weapon.h"���ɣ�������ʽΪauto weapon=Weapon::create(const std::string& filename, int attack, int mpconsuming, EAttackMode attackmode, EDebuffType debufftype);
//����������Ϊ��������������������ֵ��������ʽ��Զ��or���̣������ڵ�debuff

class Weapon :public Sprite
{
	CC_SYNTHESIZE(int, _attack, Attack);//������
	CC_SYNTHESIZE(EDebuffType, _debuff, DebuffType);//�ͷ�Debuff������
	CC_SYNTHESIZE(EAttackMode, _attackMode, AttackMode);//������ʽ
	CC_SYNTHESIZE(int, _MPConsuming, MPConsuming);//����������ֵ
public:
	virtual bool init(const std::string& filename, int attack, int mpconsuming, EAttackMode attackmode, EDebuffType debufftype);
	static Weapon* create(const std::string& filename, int attack, int mpconsuming, EAttackMode attackmode, EDebuffType debufftype);
	static Weapon* create(const std::string& filename, Weapon* wep);
	virtual bool init(const std::string& filename, Weapon* wep);
};


#endif