#pragma once
#ifndef BULLET_H_
#define BULLET_H_

#include"cocos2d.h"
#include"Component/Debuff.h"

USING_NS_CC;

class Bullet :public Sprite
{
	CC_SYNTHESIZE(int, _attack, Attack);//������
	CC_SYNTHESIZE(EDebuffType, _debuff, DebuffType);//�ͷ�Debuff������
public:
	virtual bool init(const std::string& filename,int attack,EDebuffType debufftype);
	static Bullet* create(const std::string& filename,int attack,EDebuffType debufftype);
};


#endif