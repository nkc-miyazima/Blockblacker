#include "InputManager.h"

#include <DxLib.h>

/**
 * @brief InputManager縺ｮ逕滓・繧堤ｦ∵ｭ｢縺吶ｋ縺溘ａ縺ｮ繧ｳ繝ｳ繧ｹ繝医Λ繧ｯ繧ｿ
 * @return 縺ｪ縺励・
 */
InputManager::InputManager()
    : currentPadState_(0)
    , previousPadState_(0)
{
}

/**
 * @brief InputManager縺ｮ繧､繝ｳ繧ｹ繧ｿ繝ｳ繧ｹ繧貞叙蠕・
 * @return InputManager縺ｮ蜚ｯ荳縺ｮ繧､繝ｳ繧ｹ繧ｿ繝ｳ繧ｹ
 */
InputManager& InputManager::GetInstance()
{
    static InputManager instance;
    return instance;
}

/**
 * @brief 迴ｾ蝨ｨ繝輔Ξ繝ｼ繝縺ｮ蜈･蜉帷憾諷九ｒ譖ｴ譁ｰ
 * @return 縺ｪ縺励・
 */
void InputManager::Update()
{
    // 蜑阪ヵ繝ｬ繝ｼ繝迥ｶ諷九ｒ菫晄戟縺励※謚ｼ荳・髮｢荳翫・蛻､螳壹↓菴ｿ逕ｨ
    previousKeys_ = currentKeys_;
    previousPadState_ = currentPadState_;

    GetHitKeyStateAll(currentKeys_.data());
    currentPadState_ = GetJoypadInputState(DX_INPUT_PAD1);
}

/**
 * @brief 謖・ｮ壹く繝ｼ縺後％縺ｮ繝輔Ξ繝ｼ繝縺ｧ謚ｼ縺輔ｌ縺溘°蛻､螳・
 * @param keyCode DxLib縺ｮ繧ｭ繝ｼ繧ｳ繝ｼ繝・
 * @return 謚ｼ縺輔ｌ縺溽椪髢薙↑繧液rue縲√◎繧御ｻ･螟悶・false
 */
bool InputManager::IsKeyPressed(const int keyCode) const
{
    return currentKeys_[keyCode] != 0 && previousKeys_[keyCode] == 0;
}

/**
 * @brief 謖・ｮ壹く繝ｼ縺梧款縺礼ｶ壹￠繧峨ｌ縺ｦ縺・ｋ縺句愛螳・
 * @param keyCode DxLib縺ｮ繧ｭ繝ｼ繧ｳ繝ｼ繝・
 * @return 謚ｼ荳倶ｸｭ縺ｪ繧液rue縲√◎繧御ｻ･螟悶・false
 */
bool InputManager::IsKeyHeld(const int keyCode) const
{
    return currentKeys_[keyCode] != 0;
}

/**
 * @brief 謖・ｮ壹く繝ｼ縺後％縺ｮ繝輔Ξ繝ｼ繝縺ｧ髮｢縺輔ｌ縺溘°蛻､螳・
 * @param keyCode DxLib縺ｮ繧ｭ繝ｼ繧ｳ繝ｼ繝・
 * @return 髮｢縺輔ｌ縺溽椪髢薙↑繧液rue縲√◎繧御ｻ･螟悶・false
 */
bool InputManager::IsKeyReleased(const int keyCode) const
{
    return currentKeys_[keyCode] == 0 && previousKeys_[keyCode] != 0;
}

/**
 * @brief 迴ｾ蝨ｨ縺ｮ繧ｲ繝ｼ繝繝代ャ繝牙・蜉帷憾諷九ｒ蜿門ｾ・
 * @return 繧ｲ繝ｼ繝繝代ャ繝峨・繝薙ャ繝医・繧ｹ繧ｯ迥ｶ諷・
 */
int InputManager::GetPadInput() const
{
    return currentPadState_;
}

/**
 * @brief 謖・ｮ壹・繧ｿ繝ｳ縺後％縺ｮ繝輔Ξ繝ｼ繝縺ｧ謚ｼ縺輔ｌ縺溘°蛻､螳・
 * @param buttonMask 蛻､螳壹＠縺溘＞繝懊ち繝ｳ縺ｮ繝薙ャ繝医・繧ｹ繧ｯ
 * @return 謚ｼ縺輔ｌ縺溽椪髢薙↑繧液rue縲√◎繧御ｻ･螟悶・false
 */
bool InputManager::IsPadButtonPressed(const int buttonMask) const
{
    return (currentPadState_ & buttonMask) != 0 && (previousPadState_ & buttonMask) == 0;
}

/**
 * @brief 謖・ｮ壹・繧ｿ繝ｳ縺梧款縺礼ｶ壹￠繧峨ｌ縺ｦ縺・ｋ縺句愛螳・
 * @param buttonMask 蛻､螳壹＠縺溘＞繝懊ち繝ｳ縺ｮ繝薙ャ繝医・繧ｹ繧ｯ
 * @return 謚ｼ荳倶ｸｭ縺ｪ繧液rue縲√◎繧御ｻ･螟悶・false
 */
bool InputManager::IsPadButtonHeld(const int buttonMask) const
{
    return (currentPadState_ & buttonMask) != 0;
}

/**
 * @brief 謖・ｮ壹・繧ｿ繝ｳ縺後％縺ｮ繝輔Ξ繝ｼ繝縺ｧ髮｢縺輔ｌ縺溘°蛻､螳・
 * @param buttonMask 蛻､螳壹＠縺溘＞繝懊ち繝ｳ縺ｮ繝薙ャ繝医・繧ｹ繧ｯ
 * @return 髮｢縺輔ｌ縺溽椪髢薙↑繧液rue縲√◎繧御ｻ･螟悶・false
 */
bool InputManager::IsPadButtonReleased(const int buttonMask) const
{
    return (currentPadState_ & buttonMask) == 0 && (previousPadState_ & buttonMask) != 0;
}
