#pragma once
#ifndef  HERO_H_
#define HERO_H_

#include<iostream>
#include"cocos2d.h"
#include "Constant/constant.h"
#include "Actor.h"

USING_NS_CC;

class Hero :public Actor
{
	CC_SYNTHESIZE(int, _armor, Armor);//����
	CC_SYNTHESIZE(int, _MP, MP);//������������



	/*�˰汾��Ƶ�����û���漰��װ������δ���İ汾�н��������Ľ�*/
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


};



#endif // ! HERO_H_

