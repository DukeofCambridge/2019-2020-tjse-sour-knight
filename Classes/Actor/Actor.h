#pragma once

#ifndef ACTOR_H_
#define ACTOR_H_

#include"cocos2d.h"
#include"Component/Buff.h"
#include"Component/Debuff.h"
#include"Constant/Constant.h"
#include"Equipment/Bullet.h"
#include<iostream>

USING_NS_CC;

class Actor :public Sprite
{

    CC_SYNTHESIZE(int, _HP, HP);//����ֵ
    CC_SYNTHESIZE(int, _maxHP, MaxHP);//HP���ֵ
    CC_SYNTHESIZE(int, _attack, Attack);//������
    CC_SYNTHESIZE(bool, _alreadyDead, AlreadyDead);//�ж��Ƿ��Ѿ�����
    CC_SYNTHESIZE(float, _attackRadius, AttackRadius);//������Χ�뾶
    CC_SYNTHESIZE(EAttackMode, _attactMode, AttackMode);//������ʽ
    CC_SYNTHESIZE(EDebuffType, _releaseDebuff, ReleaseDebuff);//�ͷ�Debuff������

public:
     void takeDebuff(Debuff* debuff);//���Debuff,Hero�汾����д,����汾����д
     virtual void takeDamage(Actor* actor);//
 // //////////////////////
     virtual void takeDamage(Bullet* bullet);
// ////////////////////////
     void releaseDebuff(Actor* actor);//�ͷ�debuff
     void releaseDamage(Actor* actor);//����



    virtual bool init(const std::string& filename);
    static Actor* create(const std::string& filename);
    void initData();
};


#endif // !ACTOR_H_



