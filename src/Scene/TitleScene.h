#pragma once

#include "BaseScene.h"

/**
 * @brief 繧ｿ繧､繝医Ν逕ｻ髱｢繧定｡ｨ縺吶す繝ｼ繝ｳ繧ｯ繝ｩ繧ｹ
 */
class TitleScene : public BaseScene
{
public:
    /**
     * @brief 繧ｿ繧､繝医Ν繧ｷ繝ｼ繝ｳ繧堤函謌・
     * @param sceneManager 繧ｷ繝ｼ繝ｳ驕ｷ遘ｻ繧剃ｾ晞ｼ縺吶ｋ蜈医・繝槭ロ繝ｼ繧ｸ繝｣繝ｼ
     * @return 縺ｪ縺励・
     */
    explicit TitleScene(SceneManager* sceneManager);

    /**
     * @brief 繧ｿ繧､繝医Ν繧ｷ繝ｼ繝ｳ繧堤ｴ譽・
     * @return 縺ｪ縺励・
     */
    ~TitleScene() override;

    /**
     * @brief 繧ｿ繧､繝医Ν繧ｷ繝ｼ繝ｳ縺ｮ蛻晄悄蛹・
     * @return 縺ｪ縺励・
     */
    void Init() override;

    /**
     * @brief 繧ｿ繧､繝医Ν繧ｷ繝ｼ繝ｳ縺ｮ譖ｴ譁ｰ蜃ｦ逅・
     * @return 縺ｪ縺励・
     */
    void Update() override;

    /**
     * @brief 繧ｿ繧､繝医Ν繧ｷ繝ｼ繝ｳ縺ｮ謠冗判蜃ｦ逅・
     * @return 縺ｪ縺励・
     */
    void Draw() override;
};
