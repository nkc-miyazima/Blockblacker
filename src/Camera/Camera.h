#pragma once

#include <DxLib.h>

/**
 * @brief 3D繧ｫ繝｡繝ｩ繧堤ｮ｡逅・☆繧九け繝ｩ繧ｹ
 *
 * 蝗ｺ螳壹き繝｡繝ｩ繝｢繝ｼ繝峨→霑ｽ蠕薙き繝｡繝ｩ繝｢繝ｼ繝峨ｒ繧ｵ繝昴・繝医・
 * 豈弱ヵ繝ｬ繝ｼ繝 Update() 繧貞他縺ｳ蜃ｺ縺吶％縺ｨ縺ｧ繧ｫ繝｡繝ｩ繧奪xLib縺ｫ蜿肴丐
 */
class Camera
{
public:
    /**
     * @brief 繧ｫ繝｡繝ｩ繧堤函謌舌ゅョ繝輔か繝ｫ繝医・蝗ｺ螳壹き繝｡繝ｩ繝｢繝ｼ繝・
     * @return 縺ｪ縺励・
     */
    Camera();

    /**
     * @brief 繧ｫ繝｡繝ｩ縺ｮ菴咲ｽｮ繧定ｨｭ螳夲ｼ亥崋螳壹き繝｡繝ｩ繝｢繝ｼ繝臥畑・・
     * @param pos 繧ｫ繝｡繝ｩ縺ｮ繝ｯ繝ｼ繝ｫ繝牙ｺｧ讓・
     * @return 縺ｪ縺励・
     */
    void SetPosition(VECTOR pos);

    /**
     * @brief 繧ｫ繝｡繝ｩ縺ｮ豕ｨ隕也せ繧定ｨｭ螳夲ｼ亥崋螳壹き繝｡繝ｩ繝｢繝ｼ繝臥畑・・
     * @param target 豕ｨ隕悶☆繧九Ρ繝ｼ繝ｫ繝牙ｺｧ讓・
     * @return 縺ｪ縺励・
     */
    void SetTarget(VECTOR target);

    /**
     * @brief 霑ｽ蠕薙き繝｡繝ｩ繝｢繝ｼ繝峨〒繧ｿ繝ｼ繧ｲ繝・ヨ縺ｫ霑ｽ蠕・
     * @param targetPos 霑ｽ蠕灘ｯｾ雎｡縺ｮ繝ｯ繝ｼ繝ｫ繝牙ｺｧ讓・
     * @param offset 繧ｿ繝ｼ繧ｲ繝・ヨ縺九ｉ縺ｮ繧ｫ繝｡繝ｩ縺ｮ繧ｪ繝輔そ繝・ヨ
     * @return 縺ｪ縺励・
     */
    void Follow(VECTOR targetPos, VECTOR offset);

    /**
     * @brief 逕ｻ隗抵ｼ郁ｦ夜㍽隗抵ｼ峨ｒ繝ｩ繧ｸ繧｢繝ｳ縺ｧ險ｭ螳・
     * @param fov 逕ｻ隗抵ｼ医Λ繧ｸ繧｢繝ｳ・・
     * @return 縺ｪ縺励・
     */
    void SetFov(float fov);

    /**
     * @brief 繝九い繧ｯ繝ｪ繝・・縺ｨ繝輔ぃ繝ｼ繧ｯ繝ｪ繝・・繧定ｨｭ螳・
     * @param nearClip 繝九い繧ｯ繝ｪ繝・・霍晞屬
     * @param farClip 繝輔ぃ繝ｼ繧ｯ繝ｪ繝・・霍晞屬
     * @return 縺ｪ縺励・
     */
    void SetClip(float nearClip, float farClip);

    /**
     * @brief 繧ｫ繝｡繝ｩ縺ｮ迥ｶ諷九ｒDxLib縺ｫ蜿肴丐縲よｯ弱ヵ繝ｬ繝ｼ繝蜻ｼ縺ｳ蜃ｺ縺・
     * @return 縺ｪ縺励・
     */
    void Update();

private:
    /** @brief 繧ｫ繝｡繝ｩ縺ｮ繝ｯ繝ｼ繝ｫ繝牙ｺｧ讓・*/
    VECTOR position_;

    /** @brief 繧ｫ繝｡繝ｩ縺ｮ豕ｨ隕也せ縺ｮ繝ｯ繝ｼ繝ｫ繝牙ｺｧ讓・*/
    VECTOR target_;

    /** @brief 逕ｻ隗抵ｼ医Λ繧ｸ繧｢繝ｳ・・*/
    float fov_;

    /** @brief 繝九い繧ｯ繝ｪ繝・・霍晞屬 */
    float nearClip_;

    /** @brief 繝輔ぃ繝ｼ繧ｯ繝ｪ繝・・霍晞屬 */
    float farClip_;
};
