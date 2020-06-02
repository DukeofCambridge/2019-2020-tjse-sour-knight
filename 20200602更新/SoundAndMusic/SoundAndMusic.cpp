#include "SoundAndMusic.h"
using namespace CocosDenshion;

//when you want to adjust the music and the sound, please first #include "SoundAndMusic.h" 
//�����Ҫ�������ֺ���Ч������#include "SoundAndMusic.h"

/*void init()
{
    musicCondition = true;
    soundCondition = true;
}*/

//string music��������·��;���Ҫѭ������bool loop����true
//commandֱ�Ӵ���soundToggleMenuItem->getSelectedIndex()��on->off��ʱ�����1
bool soundCondition = true;
bool musicCondition = true;
void playMusic(const char *music, const char* sound, bool loop, int command)
{
    if (command == 1)
    {
        musicCondition = false;
    }
    else {
        musicCondition = true;
    }

    if(musicCondition == true)
    {
        SimpleAudioEngine::getInstance()->playBackgroundMusic(music, loop);
        //return true;
    }
    else
    {
        SimpleAudioEngine::getInstance()->stopBackgroundMusic(music);
        //return false;
    }

    if (soundCondition == true)
    {
        SimpleAudioEngine::getInstance()->playEffect(sound);
    }
}

//soundд�ļ�·��;commandֱ�Ӵ���soundToggleMenuItem->getSelectedIndex()��on->off��ʱ�����1
void playSound(const char* sound,int command)
{
    if (soundCondition == true)
    {
        SimpleAudioEngine::getInstance()->playEffect(sound);
    }

    if (command == 1)
    {
        soundCondition = false;
    }
    else
    {
        soundCondition = true;
        SimpleAudioEngine::getInstance()->playEffect(sound);
    }
}