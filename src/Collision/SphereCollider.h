#pragma once

#include <DxLib.h>

/**
 * @brief 逅・さ繝ｩ繧､繝繝ｼ
 */
struct SphereCollider
{
    /** @brief 逅・・蜊雁ｾ・*/
    float radius;

    /** @brief 繝｢繝・Ν蜴溽せ縺九ｉ縺ｮ繧ｪ繝輔そ繝・ヨ */
    VECTOR offset;

    /**
     * @brief 逅・さ繝ｩ繧､繝繝ｼ繧堤函謌・
     * @param radius 逅・・蜊雁ｾ・
     */
    explicit SphereCollider(float radius = 1.0f)
        : radius(radius), offset(VGet(0.0f, 0.0f, 0.0f))
    {
    }

    /**
     * @brief 繧ｪ繝輔そ繝・ヨ繧定ｨｭ螳・
     * @param offset 繝｢繝・Ν蜴溽せ縺九ｉ縺ｮ繧ｪ繝輔そ繝・ヨ
     * @return 縺ｪ縺励・
     */
    void SetOffset(VECTOR offset_)
    {
        offset = offset_;
    }

    /**
     * @brief 繝ｯ繝ｼ繝ｫ繝臥ｩｺ髢薙↓縺翫￠繧狗帥縺ｮ荳ｭ蠢・ｺｧ讓吶ｒ霑斐☆
     * @param modelPos 繝｢繝・Ν縺ｮ繝ｯ繝ｼ繝ｫ繝牙ｺｧ讓・
     * @return 繝ｯ繝ｼ繝ｫ繝臥ｩｺ髢薙↓縺翫￠繧狗帥縺ｮ荳ｭ蠢・ｺｧ讓・
     */
    VECTOR GetWorldCenter(VECTOR modelPos) const
    {
        return VAdd(modelPos, offset);
    }
};
