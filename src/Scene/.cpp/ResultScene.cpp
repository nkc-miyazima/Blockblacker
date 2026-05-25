#include "ResultScene.h"
#include "../Input/InputManager.h"
#include "SceneManager.h"
#include <DxLib.h>

ResultScene::ResultScene(SceneManager* sceneManager)
    : BaseScene(sceneManager)
{
}

ResultScene::~ResultScene() = default;

void ResultScene::Init()
{
    Score = sceneManager_->lastScore;
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
    DrawFormatString(40, 80, GetColor(255, 255, 255),"Block break Score : %d", Score);
    DrawString(40, 200, "Press ENTER to Title", GetColor(255, 255, 0));
    DrawString(40, 300, "Press ESC to Exit", GetColor(255, 180, 180));
}
