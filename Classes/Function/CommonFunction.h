#pragma once
#ifndef _COMMON_FUNCTION
#define _COMMON_FUNCTION

//˵�����ڰ�ȫ��ͼ����Ϸ�ؿ���ͼ�л���ù�ͬ�ĺ�����Ϊ�����������ӣ�
//����Щ����������������һ����ͬ���ļ��У���ʹ��ʱӦ�ر�ע�⺯���Ĳ���

#include"cocos2d.h"
#include"Hero/Knight.h"
#include"Actor/Actor.h"
#include"ui/CocosGUI.h"

using namespace ui;
USING_NS_CC;

//1.informationBox�Ľ��������Ͻ������ۣ�

 void createInformationBox(Layer* layer, const Hero* hero);
//��������Layer* layer,��Ҫ�����ĸ������У�hero:����˭����Ϣ

//2.informationBox�ĸ��£���ֵ�ĸ��£�

 void updateInformationMP(Layer* layer, Hero* hero);
//�������� Layer* layer, ��Ҫ�����ĸ������У�hero:����˭����Ϣ

//3.informationBox�ĸ��£����׵ĸ��£�
 void updateInformationArmor(Layer* layer, Hero* hero);
 //�������� Layer* layer, ��Ҫ�����ĸ������У�hero:����˭����Ϣ

//4.informationBox�ĸ��£�Ѫ���ĸ��£�
 void updateInformationHP(Layer* layer, Hero* hero);
 //�������� Layer* layer, ��Ҫ�����ĸ������У�hero:����˭����Ϣ

 //5. ���׵�����
 void updateHeroArmor(Hero* hero);

//6.����ͼƬ�Ľ���
 void createSkillBox(Layer* layer,Hero* hero);
 
 //7.���ܲ۵ĸ���
 void updateSkillBox(Layer* layer,Hero* hero);

 //8.�������
 void createGoldBox(Layer*, Hero* hero);

 //9.��ҵĸ���
 void updateGoldBox(Layer* layer, Hero* hero);
#endif // !_COMMON_FUNCTION
