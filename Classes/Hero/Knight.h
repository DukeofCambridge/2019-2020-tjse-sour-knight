#pragma once
/*
��������һ�汾�������ɫ�д���������Ŀ�����
������ʵ����������Ŀ�����ʱ���Դ�����в���
*/
#ifndef  KNIGHT_H_
#define KNIGHHT_H_

#include"Actor/Hero.h"
#include"Constant/Constant.h"
#include<iostream>

class Knight :public Hero
{
public:
	//�ڶ���������װ����������������ʽ�����������ں󼸸��汾ʵ��
	virtual bool init(const std::string& filename, const::String& equipment, EAttackMode attackmode);
	//�ڶ���������װ����������������ʽ�����������ں󼸸��汾ʵ��
	static Knight* create(const std::string& filename,const::String& equipment,EAttackMode attackmode);
     
	void skillOfKnight();
};



#endif // ! KNIGHT_H_

