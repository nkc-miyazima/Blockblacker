#pragma once

#include "BaseScene.h"
#include "GameScene2D.h"

class ResultScene : public BaseScene
{
public:
    explicit ResultScene(SceneManager* sceneManager);

    ~ResultScene() override;

    void Init() override;

    void Update() override;

    void Draw() override;

private:
    int Score;
};
