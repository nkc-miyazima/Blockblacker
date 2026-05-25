#pragma once
#include <string>

/** @brief スキルの内容*/
enum class SkillType {
    PaddleLengthUp,
    PaddleSpeedUp,
    BallSpeedDown,
    BallPierce,
    ExtraLife,
    // 追加していけばOK
};

/** @brief スキルのレアリティ*/
enum class SkillRarity {
    Common,
    Rare,
    Epic,
    Legendary
};

struct Skill {
    SkillType type;
    SkillRarity rarity;
    std::string name;
    std::string description;
};
