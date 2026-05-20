#include "ResultScene.h"
#include "../Input/InputManager.h"
#include "SceneManager.h"
#include <DxLib.h>

ResultScene::ResultScene(SceneManager* sceneManager)
    : BaseScene(sceneManager),
    game2d_(sceneManager)
{
}

ResultScene::~ResultScene() = default;

void ResultScene::Init()
{
    Score = sceneManager_->lastScore;
    PlayerLive = sceneManager_->lastLives;

    LifeBonus = PlayerLive * 1000;
    FinalScore = Score + LifeBonus;
}

void ResultScene::Update()
{
    if (InputManager::GetInstance().IsKeyPressed(KEY_INPUT_RETURN))
    {
        sceneManager_->ChangeScene(SceneID::Title);
    }
}

void ResultScene::Draw()
{
    DrawString(40, 40, "Result Scene", GetColor(255, 255, 255));

    DrawFormatString(40, 80, GetColor(255, 255, 255),
        "Block break Score : %d", Score);

    DrawFormatString(40, 120, GetColor(255, 255, 255),
        "Player Life Bonus : %d * 1000 = %d", PlayerLive, LifeBonus);

    DrawFormatString(40, 160, GetColor(255, 255, 255),
        "Final Score : %d + %d = %d", Score, LifeBonus, FinalScore);

    DrawString(40, 200, "Press ENTER to Title", GetColor(255, 255, 0));
    DrawString(40, 300, "Press ESC to Exit", GetColor(255, 180, 180));
}
