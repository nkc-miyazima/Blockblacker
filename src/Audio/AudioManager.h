#pragma once

#include <string>

/**
 * @brief BGM繝ｻSE縺ｮ隱ｭ縺ｿ霎ｼ縺ｿ縺ｨ蜀咲函繧堤ｮ｡逅・☆繧九す繝ｳ繧ｰ繝ｫ繝医Φ繧ｯ繝ｩ繧ｹ
 */
class AudioManager
{
public:
    /**
     * @brief AudioManager縺ｮ繧､繝ｳ繧ｹ繧ｿ繝ｳ繧ｹ繧貞叙蠕・
     * @return AudioManager縺ｮ蜚ｯ荳縺ｮ繧､繝ｳ繧ｹ繧ｿ繝ｳ繧ｹ
     */
    static AudioManager& GetInstance();

    /**
     * @brief BGM繝輔ぃ繧､繝ｫ繧定ｪｭ縺ｿ霎ｼ縺ｿ
     * @param path 隱ｭ縺ｿ霎ｼ繧髻ｳ螢ｰ繝輔ぃ繧､繝ｫ縺ｮ繝代せ
     * @return 隱ｭ縺ｿ霎ｼ縺ｿ縺ｫ謌仙粥縺励◆繧ｵ繧ｦ繝ｳ繝峨ワ繝ｳ繝峨Ν縲∝､ｱ謨玲凾縺ｯ-1
     */
    int LoadBGM(const std::string& path) const;

    /**
     * @brief SE繝輔ぃ繧､繝ｫ繧定ｪｭ縺ｿ霎ｼ縺ｿ
     * @param path 隱ｭ縺ｿ霎ｼ繧髻ｳ螢ｰ繝輔ぃ繧､繝ｫ縺ｮ繝代せ
     * @return 隱ｭ縺ｿ霎ｼ縺ｿ縺ｫ謌仙粥縺励◆繧ｵ繧ｦ繝ｳ繝峨ワ繝ｳ繝峨Ν縲∝､ｱ謨玲凾縺ｯ-1
     */
    int LoadSE(const std::string& path) const;

    /**
     * @brief BGM繧貞・逕・
     * @param handle 蜀咲函縺吶ｋ繧ｵ繧ｦ繝ｳ繝峨ワ繝ｳ繝峨Ν
     * @param loop true縺ｪ繧峨Ν繝ｼ繝怜・逕溘’alse縺ｪ繧・蝗槫・逕・
     * @return 縺ｪ縺励・
     */
    void PlayBGM(int handle, bool loop = true) const;

    /**
     * @brief SE繧貞・逕・
     * @param handle 蜀咲函縺吶ｋ繧ｵ繧ｦ繝ｳ繝峨ワ繝ｳ繝峨Ν
     * @return 縺ｪ縺励・
     */
    void PlaySE(int handle) const;

    /**
     * @brief BGM繧貞●豁｢
     * @param handle 蛛懈ｭ｢縺吶ｋ繧ｵ繧ｦ繝ｳ繝峨ワ繝ｳ繝峨Ν
     * @return 縺ｪ縺励・
     */
    void StopBGM(int handle) const;

    /**
     * @brief BGM縺ｮ繧ｵ繧ｦ繝ｳ繝峨ワ繝ｳ繝峨Ν繧定ｧ｣謾ｾ
     * @param handle 隗｣謾ｾ縺吶ｋ繧ｵ繧ｦ繝ｳ繝峨ワ繝ｳ繝峨Ν
     * @return 縺ｪ縺励・
     */
    void UnloadBGM(int handle) const;

    /**
     * @brief SE縺ｮ繧ｵ繧ｦ繝ｳ繝峨ワ繝ｳ繝峨Ν繧定ｧ｣謾ｾ
     * @param handle 隗｣謾ｾ縺吶ｋ繧ｵ繧ｦ繝ｳ繝峨ワ繝ｳ繝峨Ν
     * @return 縺ｪ縺励・
     */
    void UnloadSE(int handle) const;

private:
    /**
     * @brief AudioManager縺ｮ逕滓・繧堤ｦ∵ｭ｢縺吶ｋ縺溘ａ縺ｮ繧ｳ繝ｳ繧ｹ繝医Λ繧ｯ繧ｿ
     * @return 縺ｪ縺励・
     */
    AudioManager();

    /**
     * @brief AudioManager縺ｮ繧ｳ繝斐・繧堤ｦ∵ｭ｢
     * @param other 繧ｳ繝斐・蜈・が繝悶ず繧ｧ繧ｯ繝・
     * @return 縺ｪ縺励・
     */
    AudioManager(const AudioManager& other) = delete;

    /**
     * @brief AudioManager縺ｮ莉｣蜈･繧堤ｦ∵ｭ｢
     * @param other 莉｣蜈･蜈・が繝悶ず繧ｧ繧ｯ繝・
     * @return 莉｣蜈･邨先棡縺ｮ蜿ら・
     */
    AudioManager& operator=(const AudioManager& other) = delete;
};
