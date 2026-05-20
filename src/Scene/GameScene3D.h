#pragma once

#include "BaseScene.h"
#include "../Camera/Camera.h"
#include "../Light/Light.h"

#include <DxLib.h>

/**
 * @brief 3D繧ｲ繝ｼ繝譛ｬ邱ｨ繧定｡ｨ縺吶す繝ｼ繝ｳ繧ｯ繝ｩ繧ｹ
 *
 * 遏｢蜊ｰ繧ｭ繝ｼ縺ｧ蠎翫ｒ蛯ｾ縺代∫帥繧定ｻ｢縺後☆繝・Δ繧ｷ繝ｼ繝ｳ
 */
class GameScene3D : public BaseScene
{
public:
    /**
     * @brief 繧ｳ繝ｳ繧ｹ繝医Λ繧ｯ繧ｿ
     * @param sceneManager 繧ｷ繝ｼ繝ｳ驕ｷ遘ｻ繧貞ｧ碑ｭｲ縺吶ｋ繝槭ロ繝ｼ繧ｸ繝｣繝ｼ
     * @return 縺ｪ縺励・
     */
    explicit GameScene3D(SceneManager* sceneManager);

    /**
     * @brief 繝・せ繝医Λ繧ｯ繧ｿ
     * @return 縺ｪ縺励・
     */
    ~GameScene3D() override;

    /**
     * @brief 蛻晄悄蛹門・逅・
     * @return 縺ｪ縺励・
     */
    void Init() override;

    /**
     * @brief 豈弱ヵ繝ｬ繝ｼ繝縺ｮ譖ｴ譁ｰ蜃ｦ逅・
     * @return 縺ｪ縺励・
     */
    void Update() override;

    /**
     * @brief 豈弱ヵ繝ｬ繝ｼ繝縺ｮ謠冗判蜃ｦ逅・
     * @return 縺ｪ縺励・
     */
    void Draw() override;

private:
    /** @brief 3D繧ｫ繝｡繝ｩ */
    Camera camera_;

    /** @brief 繝ｩ繧､繝・*/
    Light light_;

    /** @brief 蠎翫・X霆ｸ縺ｾ繧上ｊ縺ｮ蛯ｾ縺崎ｧ抵ｼ医Λ繧ｸ繧｢繝ｳ・・ 謇句燕/螂･譁ｹ蜷代・蛯ｾ縺・*/
    float floorRotX_;

    /** @brief 蠎翫・Z霆ｸ縺ｾ繧上ｊ縺ｮ蛯ｾ縺崎ｧ抵ｼ医Λ繧ｸ繧｢繝ｳ・・ 蟾ｦ蜿ｳ譁ｹ蜷代・蛯ｾ縺・*/
    float floorRotZ_;

    /** @brief 逅・・繝ｯ繝ｼ繝ｫ繝牙ｺｧ讓・*/
    VECTOR ballPos_;

    /** @brief 逅・・騾溷ｺｦ繝吶け繝医Ν・亥腰菴・ 繝ｦ繝九ャ繝・遘抵ｼ・*/
    VECTOR ballVel_;

    /** @brief 1繝輔Ξ繝ｼ繝縺ゅ◆繧翫・邨碁℃譎る俣・育ｧ抵ｼ・*/
    float deltaTime_;
};
