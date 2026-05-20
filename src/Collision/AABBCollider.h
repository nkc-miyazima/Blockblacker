#pragma once

#include <DxLib.h>

/**
 * @brief 霆ｸ蟷ｳ陦悟｢・阜繝懊ャ繧ｯ繧ｹ・・ABB・峨さ繝ｩ繧､繝繝ｼ
 */
struct AABBCollider
{
    /** @brief 繝懊ャ繧ｯ繧ｹ縺ｮ蜷・ｻｸ縺ｮ蜊雁・縺ｮ繧ｵ繧､繧ｺ */
    VECTOR halfExtents;

    /** @brief 繝｢繝・Ν蜴溽せ縺九ｉ縺ｮ繧ｪ繝輔そ繝・ヨ */
    VECTOR offset;

    /**
     * @brief AABB繧ｳ繝ｩ繧､繝繝ｼ繧堤函謌・
     * @param halfExtents 蜷・ｻｸ縺ｮ蜊雁・縺ｮ繧ｵ繧､繧ｺ
     */
    explicit AABBCollider(VECTOR halfExtents = VGet(1.0f, 1.0f, 1.0f))
        : halfExtents(halfExtents), offset(VGet(0.0f, 0.0f, 0.0f))
    {
    }

    /**
     * @brief 繝ｯ繝ｼ繝ｫ繝臥ｩｺ髢薙↓縺翫￠繧区怙蟆丞ｺｧ讓吶ｒ霑斐☆
     * @param modelPos 繝｢繝・Ν縺ｮ繝ｯ繝ｼ繝ｫ繝牙ｺｧ讓・
     * @return 繝ｯ繝ｼ繝ｫ繝臥ｩｺ髢薙↓縺翫￠繧区怙蟆丞ｺｧ讓・
     */
    VECTOR GetWorldMin(VECTOR modelPos) const
    {
        const VECTOR center = VAdd(modelPos, offset);
        return VSub(center, halfExtents);
    }

    /**
     * @brief 繝ｯ繝ｼ繝ｫ繝臥ｩｺ髢薙↓縺翫￠繧区怙螟ｧ蠎ｧ讓吶ｒ霑斐☆
     * @param modelPos 繝｢繝・Ν縺ｮ繝ｯ繝ｼ繝ｫ繝牙ｺｧ讓・
     * @return 繝ｯ繝ｼ繝ｫ繝臥ｩｺ髢薙↓縺翫￠繧区怙螟ｧ蠎ｧ讓・
     */
    VECTOR GetWorldMax(VECTOR modelPos) const
    {
        const VECTOR center = VAdd(modelPos, offset);
        return VAdd(center, halfExtents);
    }
};
