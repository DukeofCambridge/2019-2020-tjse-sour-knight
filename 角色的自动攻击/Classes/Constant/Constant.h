#pragma once
#ifndef _CONSTANT_H_
#define _CONSTANT_H_

#include"cocos2d.h";

//��ѧ���
#define PI 3.14159

//��������
#define MY_HERO_1 0x02
#define MY_HERO_2 0x01
#define ENEMY_1   0x08
#define ENEMY_2   0x04
#define MY_BULLET_1 0x04
#define MY_BULLET_2 0x08
#define ENEMY_BULLET_1 0x01
#define ENEMY_BULLET_2 0x02


//���˹�������Ѫ��
#define CREEP_HP_1 8
#define CREEP_HP_2 12
#define CREEP_HP_3 15
#define CREEP_HP_4 20
#define CREEP_HP_5 36
#define CREEP_HP_6 50

#define BOSS_HP_LOW 500
#define BOSS_HP_MEDIUN 700
#define BOSS_HP_HIGH 900

#define MONSTER_ATTACK_LOW 3
#define MONSTER_ATTACK_MEDIUN 4
#define MONSTER_ATTACK_HIGH 5

//buff��debuff
#define DEBUFF_ATTACK 1
#define NONE_DEBUFF 0


//������ʽ
enum EAttackMode
{
	MELEE=100,//��ս
	REMOTE=300//Զ�̹���
};



//Ӣ�۵���Ϣ
//Knight
#define HP_OF_KNIGHT 7
#define ARMOR_OF_KNIGHT 6
#define MP_OF_KNIGHT 200

//Tag����

//�������֣���ȫ��ͼ��ؿ���1~49
#define TAG_OF_FIRST_STAGE 1


//���ﲿ�֣�Ӣ�۽�ɫ����ˣ� 50~100
#define TAG_OF_KNIGHT 50

#define TAG_OF_ENEMY_1 60






#endif // !_CONSTANT_H_

