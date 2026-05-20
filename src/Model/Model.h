#pragma once

#include <string>
#include <variant>
#include <DxLib.h>

#include "../Collision/SphereCollider.h"
#include "../Collision/AABBCollider.h"
#include "../Collision/CapsuleCollider.h"

/**
 * @brief MV1蠖｢蠑上・3D繝｢繝・Ν縺ｮ隱ｭ縺ｿ霎ｼ縺ｿ繝ｻ謠冗判繝ｻ繧｢繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ繧堤ｮ｡逅・☆繧九け繝ｩ繧ｹ
 */
class Model
{
public:
    /**
     * @brief 繝｢繝・Ν繧堤函謌・
     * @return 縺ｪ縺励・
     */
    Model();

    /**
     * @brief 繝｢繝・Ν繧堤ｴ譽・ゅΟ繝ｼ繝画ｸ医∩縺ｮ蝣ｴ蜷医・閾ｪ蜍輔〒繧｢繝ｳ繝ｭ繝ｼ繝・
     * @return 縺ｪ縺励・
     */
    ~Model();

    /**
     * @brief MV1繝輔ぃ繧､繝ｫ繧定ｪｭ縺ｿ霎ｼ縺ｿ
     * @param filePath 隱ｭ縺ｿ霎ｼ繧繝輔ぃ繧､繝ｫ縺ｮ繝代せ
     * @return 謌仙粥縺励◆繧液rue縲∝､ｱ謨励＠縺溘ｉfalse
     */
    bool Load(const std::string& filePath);

    /**
     * @brief 繝｢繝・Ν繧偵い繝ｳ繝ｭ繝ｼ繝・
     * @return 縺ｪ縺励・
     */
    void Unload();

    /**
     * @brief 繝｢繝・Ν縺ｮ繝ｯ繝ｼ繝ｫ繝牙ｺｧ讓吶ｒ險ｭ螳・
     * @param pos 繝ｯ繝ｼ繝ｫ繝牙ｺｧ讓・
     * @return 縺ｪ縺励・
     */
    void SetPosition(VECTOR pos);

    /**
     * @brief 繝｢繝・Ν縺ｮ蝗櫁ｻ｢隗偵ｒ繝ｩ繧ｸ繧｢繝ｳ縺ｧ險ｭ螳・
     * @param rot 蜷・ｻｸ縺ｮ蝗櫁ｻ｢隗抵ｼ医Λ繧ｸ繧｢繝ｳ・・
     * @return 縺ｪ縺励・
     */
    void SetRotation(VECTOR rot);

    /**
     * @brief 繝｢繝・Ν縺ｮ繧ｹ繧ｱ繝ｼ繝ｫ繧定ｨｭ螳・
     * @param scale 蜷・ｻｸ縺ｮ繧ｹ繧ｱ繝ｼ繝ｫ
     * @return 縺ｪ縺励・
     */
    void SetScale(VECTOR scale);

    /**
     * @brief 繝｢繝・Ν縺ｮ陦悟・繧奪xLib縺ｫ蜿肴丐縲よｯ弱ヵ繝ｬ繝ｼ繝蜻ｼ縺ｳ蜃ｺ縺・
     * @return 縺ｪ縺励・
     */
    void Update();

    /**
     * @brief 繝｢繝・Ν繧呈緒逕ｻ
     * @return 縺ｪ縺励・
     */
    void Draw();

    /**
     * @brief 繧｢繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ繧貞・逕・
     * @param animIndex 蜀咲函縺吶ｋ繧｢繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ縺ｮ繧､繝ｳ繝・ャ繧ｯ繧ｹ
     * @param loop true縺ｮ縺ｨ縺阪Ν繝ｼ繝怜・逕・
     * @return 縺ｪ縺励・
     */
    void PlayAnimation(int animIndex, bool loop = true);

    /**
     * @brief 繧｢繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ繧貞●豁｢
     * @return 縺ｪ縺励・
     */
    void StopAnimation();

    /**
     * @brief 繧｢繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ縺ｮ蜀咲函譎ょ綾繧帝ｲ繧√ｋ縲よｯ弱ヵ繝ｬ繝ｼ繝蜻ｼ縺ｳ蜃ｺ縺・
     * @param deltaTime 蜑阪ヵ繝ｬ繝ｼ繝縺九ｉ縺ｮ邨碁℃譎る俣・育ｧ抵ｼ・
     * @return 縺ｪ縺励・
     */
    void UpdateAnimation(float deltaTime);

    /**
     * @brief 謖・ｮ壹い繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ縺ｮ邱丞・逕滓凾髢・
     * @param animIndex 繧｢繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ縺ｮ繧､繝ｳ繝・ャ繧ｯ繧ｹ
     * @return 邱丞・逕滓凾髢難ｼ育ｧ抵ｼ・
     */
    float GetAnimationTotalTime(int animIndex);

    /**
     * @brief 逅・さ繝ｩ繧､繝繝ｼ繧定ｨｭ螳・
     * @param col 險ｭ螳壹☆繧鬼phereCollider
     * @return 縺ｪ縺励・
     */
    void SetCollider(SphereCollider col);

    /**
     * @brief AABB繧ｳ繝ｩ繧､繝繝ｼ繧定ｨｭ螳・
     * @param col 險ｭ螳壹☆繧帰ABBCollider
     * @return 縺ｪ縺励・
     */
    void SetCollider(AABBCollider col);

    /**
     * @brief 繧ｫ繝励そ繝ｫ繧ｳ繝ｩ繧､繝繝ｼ繧定ｨｭ螳・
     * @param col 險ｭ螳壹☆繧気apsuleCollider
     * @return 縺ｪ縺励・
     */
    void SetCollider(CapsuleCollider col);

    /**
     * @brief 莉悶・繝｢繝・Ν縺ｨ縺ｮ蠖薙◆繧雁愛螳・
     * @param other 陦晉ｪ√メ繧ｧ繝・け蟇ｾ雎｡縺ｮ繝｢繝・Ν
     * @return 陦晉ｪ√＠縺ｦ縺・◆繧液rue縲√＠縺ｦ縺・↑縺代ｌ縺ｰfalse
     */
    bool CheckCollision(const Model& other);

    /**
     * @brief 繝｢繝・Ν縺ｮ繝ｯ繝ｼ繝ｫ繝牙ｺｧ讓・
     * @return 繝ｯ繝ｼ繝ｫ繝牙ｺｧ讓・
     */
    VECTOR GetPosition() const;

private:
    /** @brief DxLib縺ｮ繝｢繝・Ν繝上Φ繝峨Ν縲・1縺ｮ縺ｨ縺阪・譛ｪ繝ｭ繝ｼ繝・*/
    int modelHandle_;

    /** @brief 繝｢繝・Ν縺ｮ繝ｯ繝ｼ繝ｫ繝牙ｺｧ讓・*/
    VECTOR position_;

    /** @brief 繝｢繝・Ν縺ｮ蝗櫁ｻ｢隗抵ｼ医Λ繧ｸ繧｢繝ｳ・・*/
    VECTOR rotation_;

    /** @brief 繝｢繝・Ν縺ｮ繧ｹ繧ｱ繝ｼ繝ｫ */
    VECTOR scale_;

    /** @brief 繧｢繧ｿ繝・メ貂医∩繧｢繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ縺ｮ繝上Φ繝峨Ν縲・1縺ｮ縺ｨ縺阪・譛ｪ險ｭ螳・*/
    int animAttachIndex_;

    /** @brief 繧｢繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ縺ｮ迴ｾ蝨ｨ蜀咲函譎ょ綾・育ｧ抵ｼ・*/
    float animTime_;

    /** @brief 繧｢繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ繧偵Ν繝ｼ繝怜・逕溘☆繧九°縺ｩ縺・° */
    bool animLoop_;

    /** @brief 繧ｳ繝ｩ繧､繝繝ｼ繧呈戟縺､縺九←縺・° */
    bool hasCollider_;

    /**
     * @brief 繧ｳ繝ｩ繧､繝繝ｼ縺ｮ遞ｮ鬘槭ｒ陦ｨ縺吝・謖吝梛
     */
    enum class ColliderType { Sphere, AABB, Capsule };

    /** @brief 迴ｾ蝨ｨ險ｭ螳壹＆繧後※縺・ｋ繧ｳ繝ｩ繧､繝繝ｼ縺ｮ遞ｮ鬘・*/
    ColliderType colliderType_;

    /** @brief 繧ｳ繝ｩ繧､繝繝ｼ縺ｮ繝・・繧ｿ繧致ariant縺ｧ菫晄戟 */
    std::variant<SphereCollider, AABBCollider, CapsuleCollider> collider_;
};
