#pragma once
#include "BaseScene.h"

class TitleScene : public BaseScene
{
public:
    explicit TitleScene(SceneManager* sceneManager);

    ~TitleScene() override;

    void Init() override;

    void Update() override;

    void Draw() override;

    int selectIndex_ = 0; // 0 = BASIC, 1 = ENDLESS
};
