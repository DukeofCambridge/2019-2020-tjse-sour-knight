#pragma once
#pragma once
#ifndef __START2_SCENE_H__
#define __START2_SCENE_H__

#include "cocos2d.h"

class Start2 : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    //setting
    void menuSettingCallback(cocos2d::Ref* pSender);

    //new game
    void menuNewGameCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(Start2);
};

#endif // __START2_SCENE_H__
