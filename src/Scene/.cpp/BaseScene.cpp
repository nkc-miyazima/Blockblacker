#include "BaseScene.h"

/**
 * @brief 蝓ｺ蠎輔す繝ｼ繝ｳ繧ｯ繝ｩ繧ｹ繧貞・譛溷喧
 * @param sceneManager 繧ｷ繝ｼ繝ｳ驕ｷ遘ｻ繧剃ｾ晞ｼ縺吶ｋ蜈医・繝槭ロ繝ｼ繧ｸ繝｣繝ｼ
 * @return 縺ｪ縺励・
 */
BaseScene::BaseScene(SceneManager* sceneManager)
    : sceneManager_(sceneManager)
{
}

/**
 * @brief 蝓ｺ蠎輔す繝ｼ繝ｳ繧ｯ繝ｩ繧ｹ繧堤ｴ譽・
 * @return 縺ｪ縺励・
 */
BaseScene::~BaseScene() = default;
