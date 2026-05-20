#pragma once

#include <DxLib.h>

/**
 * @brief 繧ｷ繝｣繝峨え繝槭ャ繝励ｒ邂｡逅・☆繧九け繝ｩ繧ｹ
 *
 * 菴ｿ逕ｨ繝代ち繝ｼ繝ｳ:
 *   BeginDraw() 竊・蠖ｱ繧定誠縺ｨ縺吶Δ繝・Ν縺ｮ謠冗判 竊・EndDraw()
 *   Apply()     竊・繧ｷ繝ｼ繝ｳ蜈ｨ菴薙・謠冗判       竊・Clear()
 */
// 豕ｨ諢・ 繧ｷ繝｣繝峨え繝槭ャ繝励・MV1DrawModel()縺ｧ謠冗判縺励◆MV1繝｢繝・Ν縺ｫ縺ｮ縺ｿ譛牙柑
// DrawTriangle3D繝ｻDrawSphere3D 遲峨・繝励Μ繝溘ユ繧｣繝匁緒逕ｻ髢｢謨ｰ縺ｫ縺ｯ髱槫ｯｾ蠢・
// MV1繝｢繝・Ν繧剃ｽｿ逕ｨ縺吶ｋ繧ｷ繝ｼ繝ｳ縺ｧ縺ｮ縺ｿ蛻ｩ逕ｨ縺吶ｋ縺薙→
class ShadowMap
{
public:
    /**
     * @brief 繧ｷ繝｣繝峨え繝槭ャ繝励ｒ逕滓・
     * @return 縺ｪ縺励・
     */
    ShadowMap();

    /**
     * @brief 繧ｷ繝｣繝峨え繝槭ャ繝励ｒ遐ｴ譽・
     * @return 縺ｪ縺励・
     */
    ~ShadowMap();

    /**
     * @brief 繧ｷ繝｣繝峨え繝槭ャ繝励ｒ蛻晄悄蛹悶ゅす繝ｼ繝ｳ髢句ｧ区凾縺ｫ1蝗槫他縺ｳ蜃ｺ縺・
     * @param width  繧ｷ繝｣繝峨え繝槭ャ繝励・讓ｪ隗｣蜒丞ｺｦ・亥､ｧ縺阪＞縺ｻ縺ｩ邊ｾ邏ｰ・・
     * @param height 繧ｷ繝｣繝峨え繝槭ャ繝励・邵ｦ隗｣蜒丞ｺｦ
     * @return 謌仙粥縺励◆繧液rue縲∝､ｱ謨励＠縺溘ｉfalse
     */
    bool Init(int width = 1024, int height = 1024);

    /**
     * @brief 繧ｷ繝｣繝峨え繝槭ャ繝励ｒ隗｣謾ｾ
     * @return 縺ｪ縺励・
     */
    void Finalize();

    /**
     * @brief 蠖ｱ繧定誠縺ｨ縺吶Λ繧､繝医・譁ｹ蜷代ｒ險ｭ螳・
     * @param dir 繝ｩ繧､繝医・譁ｹ蜷代・繧ｯ繝医Ν
     * @return 縺ｪ縺励・
     */
    void SetLightDirection(VECTOR dir);

    /**
     * @brief 繧ｷ繝｣繝峨え繝槭ャ繝励′隕・≧遽・峇繧定ｨｭ螳・
     * @param center 遽・峇縺ｮ荳ｭ蠢・ｺｧ讓・
     * @param range  蜊雁ｾ・
     * @return 縺ｪ縺励・
     */
    void SetArea(VECTOR center, float range);

    /**
     * @brief 繧ｷ繝｣繝峨え繝槭ャ繝励∈縺ｮ謠冗判繧帝幕蟋・
     * @return 縺ｪ縺励・
     */
    void BeginDraw();

    /**
     * @brief 繧ｷ繝｣繝峨え繝槭ャ繝励∈縺ｮ謠冗判繧堤ｵゆｺ・
     * @return 縺ｪ縺励・
     */
    void EndDraw();

    /**
     * @brief 繧ｷ繝｣繝峨え繝槭ャ繝励ｒ繝ｬ繝ｳ繝繝ｪ繝ｳ繧ｰ縺ｫ驕ｩ逕ｨ
     * @return 縺ｪ縺励・
     */
    void Apply();

    /**
     * @brief 繧ｷ繝｣繝峨え繝槭ャ繝励・驕ｩ逕ｨ繧定ｧ｣髯､
     * @return 縺ｪ縺励・
     */
    void Clear();

private:
    /** @brief DxLib縺ｮ繧ｷ繝｣繝峨え繝槭ャ繝励ワ繝ｳ繝峨Ν縲・1縺ｮ縺ｨ縺阪・譛ｪ蛻晄悄蛹・*/
    int shadowMapHandle_;
};
