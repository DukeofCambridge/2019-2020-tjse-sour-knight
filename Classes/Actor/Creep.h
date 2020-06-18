#pragma once
#ifndef CREEP_H_
#define CREEP_H_

#include"Constant/Constant.h"
#include"Actor.h"
#include"Component/Debuff.h"
#include<iostream>

//˵���������������һ��С�֣�ֻ��auto creep=Creep::create(filename,debuffType,attackMode,HP,attack)����
//�����ֱ�����ļ�·����debuffЧ����������ʽ��Ѫ������������ע�����е�ö�����Ͳ���
class Creep :public Actor
{
public:
	virtual bool init(const std::string& filename,
		const EDebuffType debufftype,
		const EAttackMode attackmode,
		const int HP,
		const int attack,
		bool active);
		bool active;//active�����Ƿ��Ծ
	static Creep* create(const std::string &filename,
		                 const EDebuffType debufftype,
		                 const EAttackMode attackmode,
		                 const int HP,
		                 const int attack,
						 bool active);
};



#endif
