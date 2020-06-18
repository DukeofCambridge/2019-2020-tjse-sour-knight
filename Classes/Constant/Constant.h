#pragma once
#ifndef _CONSTANT_H_
#define _CONSTANT_H_

#include"cocos2d.h"

//��ѧ���
#define PI 3.14159

//��������(������ײ���)

#define WEAPON_1 0x00//Զ������ͨ������
#define WEAPON_2 0x00
#define MY_HERO_1 0x02
#define MY_HERO_2 0x01
#define ENEMY_1   0x08
#define ENEMY_2   0x04
#define MY_BULLET_1 0x04  //Ӣ�۵�Զ�������ӵ��ͽ�ս����
#define MY_BULLET_2 0x08
#define ENEMY_BULLET_1 0x01//���˵�Զ�������ӵ��ͽ�ս����
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
	ENEMY_REMOTE=300,//Զ�̹���
	HERO_REMOTE=500 //Ӣ��-Զ�̹�����Χ
	
};


//Ӣ�۵���Ϣ
//Knight
#define HP_OF_KNIGHT 7
#define ARMOR_OF_KNIGHT 6
#define MP_OF_KNIGHT 200

//Tag����

//�������֣���ȫ��ͼ��ؿ���1~34
#define TAG_OF_FIRST_STAGE_LAYER 1
#define TAG_OF_FIRST_STAGE_SCENE 2
#define TAG_OF_LEVEL_01 3


//������ͼ����
#define SIZE_OF_HERO 35

//���ﲿ�֣�Ӣ�۽�ɫ����ˣ� 50~200
#define TAG_OF_KNIGHT 50

//С��tag
#define TAG_OF_MONSTER_1 55
#define TAG_OF_MONSTER_2 56
#define TAG_OF_MONSTER_3 57
#define TAG_OF_MONSTER_4 58
#define TAG_OF_MONSTER_5 59

//Ŀǰ�ŵ���69
#define MAX_TAG_OF_MONSTER 84


//��Ϣ�����֣�HP��MP�����ף�201~250
#define TAG_OF_LABEL_HP 201
#define TAG_OF_LABEL_ARMOR 202
#define TAG_OF_LABEL_MP 203

#define TAG_OF_HP_BAR 204
#define TAG_OF_ARMOR_BAR 205
#define TAG_OF_MP_BAR 206

#define TAG_OF_INFORMATION_BOX_BAR 207

//�����Ų��� 251~299

#define TAG_OG_SAFEMAP_DOOR 251


//�������� 300~349

#define TAG_OF_KNIGHT_INITIAL_WEAPON 300

//�ӵ����� 350~400
#define TAG_OF_BULLET_01 350




#endif // !_CONSTANT_H_

