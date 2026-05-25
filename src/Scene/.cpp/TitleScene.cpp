#include "TitleScene.h"
#include "../Input/InputManager.h"
#include "SceneManager.h"
#include <DxLib.h>

TitleScene::TitleScene(SceneManager* sceneManager)
    : BaseScene(sceneManager)
{
}

TitleScene::~TitleScene() = default;

void TitleScene::Init()
{

}

void TitleScene::Update()
{
    InputManager& input = InputManager::GetInstance();

    if (input.IsKeyPressed(KEY_INPUT_UP))
    {
        selectIndex_ = 0;
    }
    if (input.IsKeyPressed(KEY_INPUT_DOWN))
    {
        selectIndex_ = 1;
    }

    if (input.IsKeyPressed(KEY_INPUT_RETURN))
    {
        if (selectIndex_ == 0)
            sceneManager_->ChangeScene(SceneID::Game2D_Basic);
        else
            sceneManager_->ChangeScene(SceneID::Game2D_Endless);
    }
}

void TitleScene::Draw()
{
    DrawString(40, 40, "Select Mode", GetColor(255, 255, 255));

    int colorBasic = (selectIndex_ == 0) ? GetColor(255, 255, 0) : GetColor(200, 200, 200);
    int colorEndless = (selectIndex_ == 1) ? GetColor(255, 255, 0) : GetColor(200, 200, 200);

    DrawString(60, 100, "BASIC MODE", colorBasic);
    DrawString(60, 140, "ENDLESS MODE", colorEndless);
}
