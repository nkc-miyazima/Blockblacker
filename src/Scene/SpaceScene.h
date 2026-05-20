#pragma once

#include "BaseScene.h"
#include "../Camera/Camera.h"

#include <vector>
#include <DxLib.h>

/**
 * @brief 繝ｯ繧､繝､繝ｼ繝輔Ξ繝ｼ繝繧ｹ繝壹・繧ｹ繧ｷ繝･繝ｼ繧ｿ繝ｼ繧ｷ繝ｼ繝ｳ
 *
 * 閾ｪ讖溘′閾ｪ蜍募燕騾ｲ縺励∫泙蜊ｰ繧ｭ繝ｼ縺ｧ荳贋ｸ句ｷｦ蜿ｳ縺ｫ遘ｻ蜍・
 * 繧ｹ繝壹・繧ｹ繧ｭ繝ｼ縺ｧ蠑ｾ繧堤匱蟆・＠縺ｦ髫懷ｮｳ迚ｩ繧堤ｴ螢翫☆繧九ョ繝｢繧ｷ繝ｼ繝ｳ
 */
class SpaceScene : public BaseScene
{
public:
    /** @brief 髫懷ｮｳ迚ｩ縺ｮ遞ｮ蛻･ */
    enum class ObstacleType { Sphere, Box };

    /** @brief 蠑ｾ縺ｮ繝・・繧ｿ */
    struct Bullet
    {
        VECTOR pos;   // 繝ｯ繝ｼ繝ｫ繝牙ｺｧ讓・
        bool   alive; // 逕溷ｭ倥ヵ繝ｩ繧ｰ
    };

    /** @brief 髫懷ｮｳ迚ｩ縺ｮ繝・・繧ｿ */
    struct Obstacle
    {
        VECTOR       pos;          // 繝ｯ繝ｼ繝ｫ繝牙ｺｧ讓・
        ObstacleType type;         // 逅・or 邂ｱ
        float        sphereRadius; // 逅・ち繧､繝励・蠖薙◆繧雁愛螳壼濠蠕・
        VECTOR       boxHalf;      // 邂ｱ繧ｿ繧､繝励・繝上・繝輔し繧､繧ｺ
        bool         alive;        // 逕溷ｭ倥ヵ繝ｩ繧ｰ
    };

    /**
     * @brief 繧ｳ繝ｳ繧ｹ繝医Λ繧ｯ繧ｿ
     * @param sceneManager 繧ｷ繝ｼ繝ｳ驕ｷ遘ｻ繧貞ｧ碑ｭｲ縺吶ｋ繝槭ロ繝ｼ繧ｸ繝｣繝ｼ
     * @return 縺ｪ縺励・
     */
    explicit SpaceScene(SceneManager* sceneManager);

    /**
     * @brief 繝・せ繝医Λ繧ｯ繧ｿ
     * @return 縺ｪ縺励・
     */
    ~SpaceScene() override;

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
    // 髫懷ｮｳ迚ｩ縺御ｸ崎ｶｳ縺励※縺・ｌ縺ｰ霑ｽ蜉繧ｹ繝昴・繝ｳ
    void SpawnObstaclesIfNeeded();

    // 繧ｹ繧ｯ繝ｭ繝ｼ繝ｫ繧ｰ繝ｪ繝・ラ繧呈緒逕ｻ
    void DrawGrid() const;

    Camera camera_;

    VECTOR playerPos_;   // 閾ｪ讖溘・繝ｯ繝ｼ繝ｫ繝牙ｺｧ讓・
    float  playerTiltX_; // 荳贋ｸ句・蜉帙↓繧医ｋX霆ｸ繝舌Φ繧ｯ隗・(繝ｩ繧ｸ繧｢繝ｳ)
    float  playerTiltZ_; // 蟾ｦ蜿ｳ蜈･蜉帙↓繧医ｋZ霆ｸ繝舌Φ繧ｯ隗・(繝ｩ繧ｸ繧｢繝ｳ)

    std::vector<Bullet>   bullets_;   // 繧｢繧ｯ繝・ぅ繝悶↑蠑ｾ繝ｪ繧ｹ繝・
    std::vector<Obstacle> obstacles_; // 繧｢繧ｯ繝・ぅ繝悶↑髫懷ｮｳ迚ｩ繝ｪ繧ｹ繝・

    int   lives_;      // 谿九ｊ繝ｩ繧､繝・
    int   startTime_;  // 繧ｷ繝ｼ繝ｳ髢句ｧ区凾蛻ｻ (GetNowCount 縺ｮ謌ｻ繧雁､)
    bool  isGameOver_; // 繧ｲ繝ｼ繝繧ｪ繝ｼ繝舌・繝輔Λ繧ｰ
    bool  isClear_;    // 繧ｯ繝ｪ繧｢繝輔Λ繧ｰ
    float endTimer_;   // 邨ゆｺ・ｼ泌・繧ｿ繧､繝槭・ (遘・

    float deltaTime_;  // 1繝輔Ξ繝ｼ繝縺ｮ邨碁℃譎る俣 (遘・
};
