#include "../.h/SoundManager.h"

SoundManager& SoundManager::GetInstance()
{
    static SoundManager instance;
    return instance;
}

void SoundManager::Load()
{
    seHandles_[SE_BREAK] = LoadSoundMem("assets/se/ƒKƒ‰ƒX‚ªŠ„‚ê‚é3.mp3");
    seHandles_[SE_PADDLE] = LoadSoundMem("assets/se/ƒpƒhƒ‹.mp3");

    // š ¡‚Í‹ó‚ÅOKBŒã‚Å‰¹‘fŞ‚ª‘µ‚Á‚½‚ç‚±‚±‚É‘‚­ š
    // seHandles_[SE_BREAK] = LoadSoundMem("assets/se/break.wav");
}

void SoundManager::PlaySE(int id)
{
    if (seHandles_[id] != -1) 
    {
        PlaySoundMem(seHandles_[id], DX_PLAYTYPE_BACK);
    }
}

void SoundManager::PlayBGM(int id)
{
    if (bgmHandles_[id] != -1) 
    {
        PlaySoundMem(bgmHandles_[id], DX_PLAYTYPE_LOOP);
    }
}

void SoundManager::StopBGM()
{
    // ‘S BGM ’â~iG‚¾‚¯‚Ç˜g‚Æ‚µ‚Ä‚Í\•ªj
    for (int i = 0; i < BGM_MAX; i++) 
    {
        if (bgmHandles_[i] != -1) 
        {
            StopSoundMem(bgmHandles_[i]);
        }
    }
}
