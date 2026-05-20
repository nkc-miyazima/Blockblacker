#pragma once

#include <DxLib.h>

/**
 * @brief 繧ｫ繝励そ繝ｫ繧ｳ繝ｩ繧､繝繝ｼ縲ゅき繝励そ繝ｫ縺ｯ縲檎ｭ抵ｼ倶ｸ｡遶ｯ縺ｮ蜊顔帥縲阪・蠖｢迥ｶ
 */
struct CapsuleCollider
{
    /** @brief 繧ｫ繝励そ繝ｫ縺ｮ蜊雁ｾ・*/
    float radius;

    /** @brief 繧ｫ繝励そ繝ｫ縺ｮ鬮倥＆・井ｸ｡遶ｯ縺ｮ蜊顔帥繧帝勁縺・◆蜀・ｭ帝Κ蛻・ｼ・*/
    float height;

    /** @brief 繝｢繝・Ν蜴溽せ縺九ｉ縺ｮ繧ｪ繝輔そ繝・ヨ */
    VECTOR offset;

    /**
     * @brief 繧ｫ繝励そ繝ｫ繧ｳ繝ｩ繧､繝繝ｼ繧堤函謌・
     * @param radius 蜊雁ｾ・
     * @param height 蜀・ｭ帝Κ蛻・・鬮倥＆
     */
    explicit CapsuleCollider(float radius = 0.5f, float height = 2.0f)
        : radius(radius), height(height), offset(VGet(0.0f, 0.0f, 0.0f))
    {
    }

    /**
     * @brief 繝ｯ繝ｼ繝ｫ繝臥ｩｺ髢薙↓縺翫￠繧倶ｸ顔ｫｯ縺ｮ荳ｭ蠢・ｺｧ讓吶ｒ霑斐☆
     * @param modelPos 繝｢繝・Ν縺ｮ繝ｯ繝ｼ繝ｫ繝牙ｺｧ讓・
     * @return 繝ｯ繝ｼ繝ｫ繝臥ｩｺ髢薙↓縺翫￠繧倶ｸ顔ｫｯ縺ｮ荳ｭ蠢・ｺｧ讓・
     */
    VECTOR GetWorldTop(VECTOR modelPos) const
    {
        const VECTOR base = VAdd(modelPos, offset);
        return VGet(base.x, base.y + height * 0.5f, base.z);
    }

    /**
     * @brief 繝ｯ繝ｼ繝ｫ繝臥ｩｺ髢薙↓縺翫￠繧倶ｸ狗ｫｯ縺ｮ荳ｭ蠢・ｺｧ讓吶ｒ霑斐☆
     * @param modelPos 繝｢繝・Ν縺ｮ繝ｯ繝ｼ繝ｫ繝牙ｺｧ讓・
     * @return 繝ｯ繝ｼ繝ｫ繝臥ｩｺ髢薙↓縺翫￠繧倶ｸ狗ｫｯ縺ｮ荳ｭ蠢・ｺｧ讓・
     */
    VECTOR GetWorldBottom(VECTOR modelPos) const
    {
        const VECTOR base = VAdd(modelPos, offset);
        return VGet(base.x, base.y - height * 0.5f, base.z);
    }
};
