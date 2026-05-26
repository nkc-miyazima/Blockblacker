#include "../.h/SceneManager.h"
#include "../.h/BaseScene.h"
#include "../.h/GameScene2D.h"
#include "../.h/ResultScene.h"
#include "../.h/TitleScene.h"

SceneManager::SceneManager() = default;

SceneManager::~SceneManager() = default;

void SceneManager::ChangeScene(const SceneID sceneID)
{
    switch (sceneID)
    {
    case SceneID::Title:
        currentScene_ = std::make_unique<TitleScene>(this);
        break;
    case SceneID::Game2D_Basic:
        currentScene_ = std::make_unique<GameScene2D>(this, GameScene2D::GameMode::Basic);
        break;
    case SceneID::Game2D_Endless:
        currentScene_ = std::make_unique<GameScene2D>(this, GameScene2D::GameMode::Endless);
        break;
    case SceneID::Result:
        currentScene_ = std::make_unique<ResultScene>(this);
        break;
    default:
        return;
    }

    if (currentScene_)
    {
        currentScene_->Init();
    }
}

void SceneManager::Update()
{
    if (currentScene_)
    {
        currentScene_->Update();
    }
}

void SceneManager::Draw() const
{
    if (currentScene_)
    {
        currentScene_->Draw();
    }
}
