#include "TitleScene.h"

#include "../Input/InputManager.h"
#include "SceneManager.h"

#include <DxLib.h>

/**
 * @brief 繧ｿ繧､繝医Ν繧ｷ繝ｼ繝ｳ繧堤函謌・
 * @param sceneManager 繧ｷ繝ｼ繝ｳ驕ｷ遘ｻ繧剃ｾ晞ｼ縺吶ｋ蜈医・繝槭ロ繝ｼ繧ｸ繝｣繝ｼ
 * @return 縺ｪ縺励・
 */
TitleScene::TitleScene(SceneManager* sceneManager)
    : BaseScene(sceneManager)
{
}

/**
 * @brief 繧ｿ繧､繝医Ν繧ｷ繝ｼ繝ｳ繧堤ｴ譽・
 * @return 縺ｪ縺励・
 */
TitleScene::~TitleScene() = default;

/**
 * @brief 繧ｿ繧､繝医Ν繧ｷ繝ｼ繝ｳ縺ｮ蛻晄悄蛹・
 * @return 縺ｪ縺励・
 */
void TitleScene::Init()
{
    // TODO: 繧ｿ繧､繝医Ν繝ｭ繧ｴ縺ｮ逕ｻ蜒剰ｪｭ縺ｿ霎ｼ縺ｿ繧ВGM蜀咲函髢句ｧ句・逅・ｒ霑ｽ蜉
}

/**
 * @brief 繧ｿ繧､繝医Ν繧ｷ繝ｼ繝ｳ縺ｮ譖ｴ譁ｰ蜃ｦ逅・
 * @return 縺ｪ縺励・
 */
void TitleScene::Update()
{
    // Enter繧ｭ繝ｼ繧呈款縺励◆迸ｬ髢薙↓繧ｲ繝ｼ繝譛ｬ邱ｨ縺ｸ驕ｷ遘ｻ縺吶ｋ繧ｵ繝ｳ繝励Ν
    if (InputManager::GetInstance().IsKeyPressed(KEY_INPUT_RETURN))
    {
        sceneManager_->ChangeScene(SceneID::Game2D);
    }

    // TODO: 繝｡繝九Η繝ｼ驕ｸ謚槫・逅・ｄ髮｣譏灘ｺｦ驕ｸ謚槫・逅・ｒ縺薙％縺ｫ霑ｽ蜉
}

/**
 * @brief 繧ｿ繧､繝医Ν繧ｷ繝ｼ繝ｳ縺ｮ謠冗判蜃ｦ逅・
 * @return 縺ｪ縺励・
 */
void TitleScene::Draw()
{
    DrawString(40, 40, "Title Scene", GetColor(255, 255, 255));
    DrawString(40, 80, "Press ENTER to Start", GetColor(255, 255, 0));
    DrawString(40, 120, "Press ESC to Exit", GetColor(255, 180, 180));
    // TODO: 繧ｿ繧､繝医Ν閭梧勹繧ФI逕ｻ蜒上・謠冗判蜃ｦ逅・ｒ縺薙％縺ｫ霑ｽ蜉
}
