#pragma once

#ifndef  _KNIGHT_H_
#define _KNIGHHT_H_

#include"Actor/Hero.h"
#include"Constant/Constant.h"
#include<iostream>
#include"Equipment/Weapon.h"

//˵����������һ����ʿӢ�ۣ�ֻ��auto knight=Knight::create(const std::string& filename,Weapon* weapon)
//ǰ��Ϊ�ļ�·��������Ϊ��ʿ��װ��������
//ע�⣡����������Ӣ����ʱ��֧���������л�
class Knight :public Hero
{

public:
	virtual bool init(const std::string& filename,Weapon* weapon);
	
	static Knight* create(const std::string& filename,Weapon* weapon);
     
	
};



#endif // ! KNIGHT_H_

