#include "Settings/SoundAndMusic.h"
using namespace CocosDenshion;

//when you want to adjust the music and the sound, please first #include "SoundAndMusic.h" 
//�����Ҫ�������ֺ���Ч������#include "SoundAndMusic.h"

//string music��������·��;���Ҫѭ������bool loop����true
//commandֱ�Ӵ���soundToggleMenuItem->getSelectedIndex()��on->off��ʱ�����1
bool soundCondition = true;
bool musicCondition = true;
bool doContinueGame = false;
float musicVolume = 1;
float soundVolumn = 1;

void playMusic(const char *music, bool loop, int command)
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
        SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(musicVolume);
    }
    else
    {
        SimpleAudioEngine::getInstance()->stopBackgroundMusic(music);
    }
}

void playMusic(const char* music, bool loop)
{
    if (musicCondition == true)
    {
        SimpleAudioEngine::getInstance()->playBackgroundMusic(music, loop);
        SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(musicVolume);
    }
    else
    {
        SimpleAudioEngine::getInstance()->stopBackgroundMusic(music);
    }
}

//soundд�ļ�·��;commandֱ�Ӵ���soundToggleMenuItem->getSelectedIndex()��on->off��ʱ�����1
void playSound(const char* sound,int command)
{
    if (soundCondition == true)
    {
        SimpleAudioEngine::getInstance()->playEffect(sound);
        SimpleAudioEngine::getInstance()->setEffectsVolume(soundVolumn);
    }

    if (command == 1)
    {
        soundCondition = false;
    }
    else
    {
        soundCondition = true;
    }
}

void playSound(const char* sound)
{
    if (soundCondition == true)
    {
        SimpleAudioEngine::getInstance()->playEffect(sound);
        SimpleAudioEngine::getInstance()->setEffectsVolume(soundVolumn);
    }
}

void MusicVolumnIncrease()
{
    float OrigionVolumnMusic = SimpleAudioEngine::getInstance()->getBackgroundMusicVolume();
    float volumnMusic = OrigionVolumnMusic + 0.1;
    if (volumnMusic > 1)
    {
        volumnMusic = 1;
    }
    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(volumnMusic);
    musicVolume = volumnMusic;

}
void MusicVolumnDecrease()
{
    float OrigionVolumnMusic = SimpleAudioEngine::getInstance()->getBackgroundMusicVolume();
    float volumnMusic  = OrigionVolumnMusic - 0.1;
    if (volumnMusic < 0)
    {
        volumnMusic = 0;
    }
    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(volumnMusic);
    musicVolume = volumnMusic;
}

void SoundVolumnIncrease()
{
    float OrigionVolumnSound = SimpleAudioEngine::getInstance()->getEffectsVolume();
    float volumnSound = OrigionVolumnSound +0.1;
    if (volumnSound > 1)
    {
        volumnSound = 1;
    }
    SimpleAudioEngine::getInstance()->setEffectsVolume(volumnSound);
    soundVolumn = volumnSound;
    //SimpleAudioEngine::getInstance()->setEffectsVolume(1);
}

void SoundVolumnDecrease()
{
    float OrigionVolumnSound = SimpleAudioEngine::getInstance()->getEffectsVolume();
    float volumnSound = OrigionVolumnSound-0.1;
    if (volumnSound < 0)
    {
        volumnSound = 0;
    }
    soundVolumn = volumnSound;
    SimpleAudioEngine::getInstance()->setEffectsVolume(volumnSound);
   // SimpleAudioEngine::getInstance()->setEffectsVolume(0);
}