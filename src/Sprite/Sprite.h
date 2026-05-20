#pragma once

#include <string>

/**
 * @brief 2D逕ｻ蜒上・隱ｭ縺ｿ霎ｼ縺ｿ縺ｨ謠冗判繧堤ｰ｡蜊倥↓謇ｱ縺・せ繝励Λ繧､繝医け繝ｩ繧ｹ
 */
class Sprite
{
public:
    /**
     * @brief 逕ｻ蜒上ヵ繧｡繧､繝ｫ繧定ｪｭ縺ｿ霎ｼ繧薙〒繧ｹ繝励Λ繧､繝医ｒ逕滓・
     * @param filePath 隱ｭ縺ｿ霎ｼ繧逕ｻ蜒上ヵ繧｡繧､繝ｫ縺ｮ繝代せ
     * @return 縺ｪ縺励・
     */
    explicit Sprite(const std::string& filePath);

    /**
     * @brief 繧ｹ繝励Λ繧､繝医ｒ遐ｴ譽・
     * @return 縺ｪ縺励・
     */
    ~Sprite();

    /**
     * @brief 謖・ｮ壼ｺｧ讓吶↓繧ｹ繝励Λ繧､繝医ｒ謠冗判
     * @param x 謠冗判蜈医・X蠎ｧ讓・
     * @param y 謠冗判蜈医・Y蠎ｧ讓・
     * @return 縺ｪ縺励・
     */
    void Draw(int x, int y) const;

    /**
     * @brief 繧ｵ繧､繧ｺ謖・ｮ壹〒繧ｹ繝励Λ繧､繝医ｒ謠冗判
     * @param x 謠冗判蜈医・X蠎ｧ讓・
     * @param y 謠冗判蜈医・Y蠎ｧ讓・
     * @param width 謠冗判蟷・
     * @param height 謠冗判鬮倥＆
     * @return 縺ｪ縺励・
     */
    void Draw(int x, int y, int width, int height) const;

private:
    /** @brief DxLib縺ｮ繧ｰ繝ｩ繝輔ぅ繝・け繝上Φ繝峨Ν */
    int graphHandle_;
};
