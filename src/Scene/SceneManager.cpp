#include "SceneManager.h"

#include "BaseScene.h"
#include "GameScene2D.h"
#include "GameScene3D.h"
#include "SpaceScene.h"
#include "ResultScene.h"
#include "TitleScene.h"

SceneManager::SceneManager() = default;

SceneManager::~SceneManager() = default;

void SceneManager::ChangeScene(const SceneID sceneID)
{
    switch (sceneID)
    {
    case SceneID::Title:
        currentScene_ = std::make_unique<TitleScene>(this);
        break;
    case SceneID::Game2D:
        currentScene_ = std::make_unique<GameScene2D>(this);
        break;
    case SceneID::Game3D:
        currentScene_ = std::make_unique<GameScene3D>(this);
        break;
    case SceneID::Space:
        currentScene_ = std::make_unique<SpaceScene>(this);
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
