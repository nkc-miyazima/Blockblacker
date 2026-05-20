#pragma once

#include <DxLib.h>

/**
 * @brief 繧ｷ繝ｼ繝ｳ蜈ｨ菴薙↓蠖ｱ髻ｿ縺吶ｋ蟷ｳ陦悟・貅舌ｒ邂｡逅・☆繧九け繝ｩ繧ｹ
 */
class Light
{
public:
    /**
     * @brief 繝ｩ繧､繝医ｒ逕滓・
     * @return 縺ｪ縺励・
     */
    Light();

    /**
     * @brief 繝ｩ繧､繝医ｒ繝・ヵ繧ｩ繝ｫ繝亥､縺ｧ蛻晄悄蛹悶ゅす繝ｼ繝ｳ髢句ｧ区凾縺ｫ1蝗槫他縺ｳ蜃ｺ縺・
     * @return 縺ｪ縺励・
     */
    void Init();

    /**
     * @brief 蜈峨・蟾ｮ縺苓ｾｼ繧譁ｹ蜷代ｒ險ｭ螳・
     * @param dir 譁ｹ蜷代・繧ｯ繝医Ν・域ｭ｣隕丞喧荳崎ｦ・ｼ・
     * @return 縺ｪ縺励・
     */
    void SetDirection(VECTOR dir);

    /**
     * @brief 諡｡謨｣蜈峨・濶ｲ繧定ｨｭ螳・
     * @param color 諡｡謨｣蜈峨・濶ｲ
     * @return 縺ｪ縺励・
     */
    void SetDiffuse(COLOR_F color);

    /**
     * @brief 迺ｰ蠅・・縺ｮ濶ｲ繧定ｨｭ螳・
     * @param color 迺ｰ蠅・・縺ｮ濶ｲ
     * @return 縺ｪ縺励・
     */
    void SetAmbient(COLOR_F color);

    /**
     * @brief 髀｡髱｢蜿榊ｰ・・縺ｮ濶ｲ繧定ｨｭ螳・
     * @param color 髀｡髱｢蜿榊ｰ・・縺ｮ濶ｲ
     * @return 縺ｪ縺励・
     */
    void SetSpecular(COLOR_F color);
};
