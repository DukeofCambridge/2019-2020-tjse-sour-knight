#include "Scene/DeadScene.h"
#include "Scene/firstStage.h"

using namespace CocosDenshion;
USING_NS_CC;

//��δ����ɵ���һ�µ��ƶ�����
//δ��ʵ�ֶ��ɫѡ��ʱ����ͼ��ͬ
Scene* Dead::createScene()
{
    return Dead::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in DeadScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Dead::init()
{

    if (!Scene::init())
    {
        return false;
    }

    log("Dead init");

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    clickNum = 0;

    ////////////////���ñ���///////////////////////
    auto background1 = Sprite::create("Backgrounds/deadBackground.png");
    background1->setAnchorPoint(Point(0, 0));
    background1->setPosition(Point(0, 0));
    addChild(background1);

    ///////////////����Ӣ�۾���///////////////////
    auto player = Sprite::create("Heroes/knight1.1.png");
    player->setAnchorPoint(Vec2(0, 0));
    player->setPosition(Vec2(90, 660));
    //player->setTag(TAG_OF_PLAYER);
    addChild(player);

    //////////////���ü�����ť////////////////////
    auto continueButton = MenuItemImage::create(
        "Buttons/continue-up.png",
        "Buttons/continue-down.png", CC_CALLBACK_1(Dead::menuContinueCallback, this));
    continueButton->setAnchorPoint(Vec2(0, 0));
    continueButton->setPosition(Vec2(visibleSize.width/2 - continueButton->getContentSize().width/2, 160 - continueButton->getContentSize().height / 2));

    auto menu = Menu::create(continueButton, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);

    return true;
}

//continue
void Dead::menuContinueCallback(Ref* pSender)//���밲ȫ��
{
    //auto player = this->getChildByTag(TAG_OF_PLAYER);
    clickNum++;
    //��һ�ε�������ƶ��Ķ���
    if (clickNum == 1) 
    {
        ////ͨ����һ��
        //if (player.successNum == 1)
        //{
        //    auto moveTo = MoveTo::create(2, Vec2(440, player->getPositionY()));
        //}
        ////ͨ���ڶ���
        //else if (player.successNum == 2)
        //{
        //    auto moveTo = MoveTo::create(2, Vec2(820, player->getPositionY()));
        //}
    }
    //�ڶ��ε�����س���
    else if (clickNum == 2) {
    auto scene = firstStage::createScene();
    Director::getInstance()->replaceScene(scene);
    }
    playSound("sound/ClickSound.mp3");
}