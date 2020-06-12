#pragma once
#ifndef _COMMON_FUNCTION
#define _COMMON_FUNCTION

//说明：在安全地图与游戏关卡地图中会调用共同的函数，为避免代码的冗杂，
//将这些函数整理起来放在一个共同的文件中，在使用时应特别注意函数的参数

#include"cocos2d.h"
#include"Hero/Knight.h"
#include"Actor/Actor.h"
#include"ui/CocosGUI.h"

using namespace ui;
USING_NS_CC;

//1.informationBox的建立（左上角能量槽）

 void createInformationBox(Layer* layer, const Hero* hero);
//参数介绍Layer* layer,需要加在哪个场景中，hero:关于谁的信息

//2.informationBox的更新（蓝值的更新）

 void updateInformationMP(Layer* layer, Hero* hero);
//参数介绍 Layer* layer, 需要加在哪个场景中，hero:关于谁的信息


#endif // !_COMMON_FUNCTION
