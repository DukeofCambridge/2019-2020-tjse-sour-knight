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
#define GROUNDATTACK_1 1

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

#define MONSTER_ATTACK_LOW 2
#define MONSTER_ATTACK_MEDIUM 3
#define MONSTER_ATTACK_HIGH 4

//����Ĺ�����
#define HERO_ATTACK_LOW 3
#define HERO_ATTACK_MEDIUM 4
#define HERO_ATTACK_HIGH 5

//��ɫ����Ƶ��
#define ATTACK_FREQUENCY_1 1
#define ATTACK_FREQUENCY_2 2
#define ATTACK_FREQUENCY_3 3
#define ATTACK_FREQUENCY_4 4
#define ATTACK_FREQUENCY_5 5

//��������ֵ
#define CONSUMPTION_0 0
#define CONSUMPTION_1 1
#define CONSUMPTION_2 2
#define CONSUMPTION_3 3
#define CONSUMPTION_4 4
#define CONSUMPTION_5 5



//buff��debuff
#define DEBUFF_ATTACK 1
#define NONE_DEBUFF 0


//������ʽ
enum  EAttackMode 
{
	HERO_MELEE = 150,//��ս
	HERO_MELEE_1 = 200,
	HERO_MELEE_2 = 250,
	HERO_MELEE_3 = 300,
	HERO_MELEE_4 = 399,
	ENEMY_REMOTE = 300,//Զ�̹���
	ENEMY_REMOTE2 = 600,
	ENEMY_MELEE = 299,
	HERO_REMOTE = 400,//Ӣ��-Զ�̹�����Χ
	HERO_REMOTE_1 = 450,
	HERO_REMOTE_2 = 500,
	HERO_REMOTE_3 = 550

};



//Ӣ�۵���Ϣ
//Knight
#define HP_OF_KNIGHT 7
#define ARMOR_OF_KNIGHT 6
#define MP_OF_KNIGHT 200
#define SKILL_POINT_OF_KNIGHT 200

//Tag����

//�������֣���ȫ��ͼ��ؿ���1~34
#define TAG_OF_FIRST_STAGE_LAYER 1
#define TAG_OF_FIRST_STAGE_SCENE 2
#define TAG_OF_LEVEL_01 3
#define TAG_OF_LEVEL_02 4
#define TAG_OF_LEVEL_03 5
#define TAG_OF_LEVEL_04 6

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

//Ŀǰ�ŵ���96
#define MAX_TAG_OF_MONSTER 96


//��Ϣ�����֣�HP��MP�����ף�201~250
#define TAG_OF_LABEL_HP 201
#define TAG_OF_LABEL_ARMOR 202
#define TAG_OF_LABEL_MP 203

#define TAG_OF_HP_BAR 204
#define TAG_OF_ARMOR_BAR 205
#define TAG_OF_MP_BAR 206
#define TAG_OF_INFORMATION_BOX_BAR 207

#define TAG_OF_SKILL_BACKGROUND 208
#define TAG_OF_SKILL_POINT 209
#define TAG_OF_LABEL_GOLD 210

//�����Ų��� 251~299

#define TAG_OG_SAFEMAP_DOOR 251


//�������� 300~349

#define TAG_OF_KNIGHT_INITIAL_WEAPON 300

//�ӵ����� 350~400
#define TAG_OF_BULLET_01 350

//���߲���
#define PROPS_DRUG_HP 401
#define PROPS_DRUG_MP 402
#define PROPS_DRUG_HPMP 403
#define PROPS_GOLD 404
#define TAG_OF_PROPS_HP 405
#define TAG_OF_PROPS_MP 406
#define PROPS_DRUG_HP_FULL 407
#define PROPS_DRUG_MP_FULL 408
#define EMPTY 409
#define PRICE_OF_DRUG_HP 18
#define PRICE_OF_DRUG_MP 12
#define PRICE_OF_DRUG_HPMP 30


//������������
#define TAG_OF_PLAYER 410

#endif // !_CONSTANT_H_

