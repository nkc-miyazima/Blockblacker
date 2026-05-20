#pragma once

#include <DxLib.h>

/**
 * @brief 3D蠖｢迥ｶ繧呈緒逕ｻ縺吶ｋ繝ｦ繝ｼ繝・ぅ繝ｪ繝・ぅ繧ｯ繝ｩ繧ｹ・医ョ繝舌ャ繧ｰ陦ｨ遉ｺ縺ｪ縺ｩ縺ｫ萓ｿ蛻ｩ・・
 *
 * 縺吶∋縺ｦ縺ｮ繝｡繧ｽ繝・ラ縺ｯstatic縲ゅう繝ｳ繧ｹ繧ｿ繝ｳ繧ｹ繧剃ｽ懈・縺帙★縺ｫ菴ｿ逕ｨ蜿ｯ閭ｽ
 */
class Primitive3D
{
public:
    /**
     * @brief 逅・ｒ謠冗判
     * @param center 逅・・荳ｭ蠢・ｺｧ讓・
     * @param radius 逅・・蜊雁ｾ・
     * @param color  謠冗判濶ｲ
     * @param fill   true縺ｮ縺ｨ縺榊｡励ｊ縺､縺ｶ縺励’alse縺ｮ縺ｨ縺阪Ρ繧､繝､繝ｼ繝輔Ξ繝ｼ繝
     * @return 縺ｪ縺励・
     */
    static void DrawSphere(VECTOR center, float radius, COLOR_U8 color,
                            bool fill = true, bool lighting = false);

    /**
     * @brief 霆ｸ蟷ｳ陦悟｢・阜繝懊ャ繧ｯ繧ｹ・・ABB・峨ｒ謠冗判
     * @param min  繝懊ャ繧ｯ繧ｹ縺ｮ譛蟆丞ｺｧ讓・
     * @param max  繝懊ャ繧ｯ繧ｹ縺ｮ譛螟ｧ蠎ｧ讓・
     * @param color 謠冗判濶ｲ
     * @param fill  true縺ｮ縺ｨ縺榊｡励ｊ縺､縺ｶ縺励’alse縺ｮ縺ｨ縺阪Ρ繧､繝､繝ｼ繝輔Ξ繝ｼ繝
     * @return 縺ｪ縺励・
     */
    static void DrawBox(VECTOR min, VECTOR max, COLOR_U8 color,
                        bool fill = true, bool lighting = false);

    /**
     * @brief 邱壼・繧呈緒逕ｻ
     * @param start 蟋狗せ縺ｮ蠎ｧ讓・
     * @param end   邨らせ縺ｮ蠎ｧ讓・
     * @param color 謠冗判濶ｲ
     * @param width 邱壹・螟ｪ縺・
     * @return 縺ｪ縺励・
     */
    static void DrawLine(VECTOR start, VECTOR end, COLOR_U8 color,
                         float width = 1.0f, bool lighting = false);

    /**
     * @brief 繧ｫ繝励そ繝ｫ繧呈緒逕ｻ
     * @param start  繧ｫ繝励そ繝ｫ縺ｮ荳狗ｫｯ縺ｮ荳ｭ蠢・ｺｧ讓・
     * @param end    繧ｫ繝励そ繝ｫ縺ｮ荳顔ｫｯ縺ｮ荳ｭ蠢・ｺｧ讓・
     * @param radius 繧ｫ繝励そ繝ｫ縺ｮ蜊雁ｾ・
     * @param color  謠冗判濶ｲ
     * @param fill   true縺ｮ縺ｨ縺榊｡励ｊ縺､縺ｶ縺励’alse縺ｮ縺ｨ縺阪Ρ繧､繝､繝ｼ繝輔Ξ繝ｼ繝
     * @return 縺ｪ縺励・
     */
    static void DrawCapsule(VECTOR start, VECTOR end, float radius, COLOR_U8 color,
                             bool fill = true, bool lighting = false);

private:
    // 繧､繝ｳ繧ｹ繧ｿ繝ｳ繧ｹ蛹也ｦ∵ｭ｢
    Primitive3D() = delete;
};
