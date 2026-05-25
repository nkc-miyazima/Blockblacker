#pragma once
#pragma once
#include <DxLib.h>

class SoundManager
{
public:
    static SoundManager& GetInstance();

    void Load();                // ‰¹“Ç‚İ‚İiŒã‚Å’†g‚ğì‚éj
    void PlaySE(int id);        // SE Ä¶
    void PlayBGM(int id);       // BGM Ä¶
    void StopBGM();             // BGM ’â~

    enum SE {
        SE_BREAK,
        SE_REFLECT,
        SE_UI_DECIDE,
        SE_PADDLE,
        SE_MAX
    };

    enum BGM {
        BGM_GAME,
        BGM_TITLE,
        BGM_RESULT,
        BGM_MAX
    };

private:
    SoundManager() = default;

    int seHandles_[SE_MAX] = { -1 };
    int bgmHandles_[BGM_MAX] = { -1 };
};
