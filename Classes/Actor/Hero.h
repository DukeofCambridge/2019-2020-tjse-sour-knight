#pragma once
#ifndef  HERO_H_
#define HERO_H_

#include<iostream>
#include"cocos2d.h"
#include "Constant/constant.h"
#include"Equipment/weapon.h"
#include "Actor.h"

USING_NS_CC;

class Hero :public Actor
{
	CC_SYNTHESIZE(int, _armor, Armor);//����
	CC_SYNTHESIZE(int, _MP, MP);//������������
	CC_SYNTHESIZE(int, _MPConsuming, MPConsuming);//ÿһ�ι������ĵ�����ֵ
	CC_SYNTHESIZE(int, _maxArmor, MaxArmor);//�������ֵ
	CC_SYNTHESIZE(int, _maxMP, MaxMP);//MP���ֵ
	CC_SYNTHESIZE(float, _skillPoint, SkillPoint);//��ǰ�ļ��ܵ�
	CC_SYNTHESIZE(float, _maxSkillPoint, MaxSkillPoint);//���ļ��ܵ�
	CC_SYNTHESIZE(int, _levelNum, LevelNum);//���ؿ�
	CC_SYNTHESIZE(int, _gold, Gold);//���
	

public:
	virtual bool init(const std::string& filename,
		const EAttackMode attackmode,
		const float attackradius,
		const int HP,
		const int MP,
		const int armor,
		const int attack
	);



	static Hero* create(const std::string& filename,
		const EAttackMode attackmode,
		const float attackradius,
		const int HP,
		const int MP,
		const int armor,
		const int attack
	);

void consumeMP();

virtual void takeDamage(Actor* actor);

virtual void takeDamage(Bullet* bullet);

virtual void changeWeapon(Weapon* weapon);

};



#endif // ! HERO_H_

