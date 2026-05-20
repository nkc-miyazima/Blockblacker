#pragma once

#include "SphereCollider.h"
#include "AABBCollider.h"
#include "CapsuleCollider.h"

#include <DxLib.h>

/**
 * @brief 3D繧ｳ繝ｩ繧､繝繝ｼ髢薙・蠖薙◆繧雁愛螳壹ｒ謠蝉ｾ帙☆繧九Θ繝ｼ繝・ぅ繝ｪ繝・ぅ繧ｯ繝ｩ繧ｹ
 *
 * 縺吶∋縺ｦ縺ｮ繝｡繧ｽ繝・ラ縺ｯstatic縲ゅう繝ｳ繧ｹ繧ｿ繝ｳ繧ｹ繧剃ｽ懈・縺帙★縺ｫ菴ｿ逕ｨ蜿ｯ閭ｽ
 */
class Collision3D
{
public:
    /**
     * @brief 逅・→逅・・蠖薙◆繧雁愛螳・
     * @param a    逅・さ繝ｩ繧､繝繝ｼA
     * @param posA 繧ｳ繝ｩ繧､繝繝ｼA縺ｮ繝｢繝・Ν蠎ｧ讓・
     * @param b    逅・さ繝ｩ繧､繝繝ｼB
     * @param posB 繧ｳ繝ｩ繧､繝繝ｼB縺ｮ繝｢繝・Ν蠎ｧ讓・
     * @return 陦晉ｪ√＠縺ｦ縺・◆繧液rue縲√＠縺ｦ縺・↑縺代ｌ縺ｰfalse
     */
    static bool SphereToSphere(const SphereCollider& a, VECTOR posA,
                                const SphereCollider& b, VECTOR posB);

    /**
     * @brief AABB縺ｨAABB縺ｮ蠖薙◆繧雁愛螳・
     * @param a    AABB繧ｳ繝ｩ繧､繝繝ｼA
     * @param posA 繧ｳ繝ｩ繧､繝繝ｼA縺ｮ繝｢繝・Ν蠎ｧ讓・
     * @param b    AABB繧ｳ繝ｩ繧､繝繝ｼB
     * @param posB 繧ｳ繝ｩ繧､繝繝ｼB縺ｮ繝｢繝・Ν蠎ｧ讓・
     * @return 陦晉ｪ√＠縺ｦ縺・◆繧液rue縲√＠縺ｦ縺・↑縺代ｌ縺ｰfalse
     */
    static bool AABBToAABB(const AABBCollider& a, VECTOR posA,
                            const AABBCollider& b, VECTOR posB);

    /**
     * @brief 逅・→AABB縺ｮ蠖薙◆繧雁愛螳・
     * @param sphere 逅・さ繝ｩ繧､繝繝ｼ
     * @param posS   逅・・繝｢繝・Ν蠎ｧ讓・
     * @param aabb   AABB繧ｳ繝ｩ繧､繝繝ｼ
     * @param posA   AABB縺ｮ繝｢繝・Ν蠎ｧ讓・
     * @return 陦晉ｪ√＠縺ｦ縺・◆繧液rue縲√＠縺ｦ縺・↑縺代ｌ縺ｰfalse
     */
    static bool SphereToAABB(const SphereCollider& sphere, VECTOR posS,
                              const AABBCollider&   aabb,   VECTOR posA);

    /**
     * @brief 繧ｫ繝励そ繝ｫ縺ｨ繧ｫ繝励そ繝ｫ縺ｮ蠖薙◆繧雁愛螳・
     * @param a    繧ｫ繝励そ繝ｫ繧ｳ繝ｩ繧､繝繝ｼA
     * @param posA 繧ｳ繝ｩ繧､繝繝ｼA縺ｮ繝｢繝・Ν蠎ｧ讓・
     * @param b    繧ｫ繝励そ繝ｫ繧ｳ繝ｩ繧､繝繝ｼB
     * @param posB 繧ｳ繝ｩ繧､繝繝ｼB縺ｮ繝｢繝・Ν蠎ｧ讓・
     * @return 陦晉ｪ√＠縺ｦ縺・◆繧液rue縲√＠縺ｦ縺・↑縺代ｌ縺ｰfalse
     */
    static bool CapsuleToCapsule(const CapsuleCollider& a, VECTOR posA,
                                  const CapsuleCollider& b, VECTOR posB);

    /**
     * @brief 逅・→繧ｫ繝励そ繝ｫ縺ｮ蠖薙◆繧雁愛螳・
     * @param sphere  逅・さ繝ｩ繧､繝繝ｼ
     * @param posS    逅・・繝｢繝・Ν蠎ｧ讓・
     * @param capsule 繧ｫ繝励そ繝ｫ繧ｳ繝ｩ繧､繝繝ｼ
     * @param posC    繧ｫ繝励そ繝ｫ縺ｮ繝｢繝・Ν蠎ｧ讓・
     * @return 陦晉ｪ√＠縺ｦ縺・◆繧液rue縲√＠縺ｦ縺・↑縺代ｌ縺ｰfalse
     */
    static bool SphereToCapsule(const SphereCollider&  sphere,  VECTOR posS,
                                 const CapsuleCollider& capsule, VECTOR posC);

    /**
     * @brief AABB縺ｨ繧ｫ繝励そ繝ｫ縺ｮ蠖薙◆繧雁愛螳・
     * @param aabb    AABB繧ｳ繝ｩ繧､繝繝ｼ
     * @param posA    AABB縺ｮ繝｢繝・Ν蠎ｧ讓・
     * @param capsule 繧ｫ繝励そ繝ｫ繧ｳ繝ｩ繧､繝繝ｼ
     * @param posC    繧ｫ繝励そ繝ｫ縺ｮ繝｢繝・Ν蠎ｧ讓・
     * @return 陦晉ｪ√＠縺ｦ縺・◆繧液rue縲√＠縺ｦ縺・↑縺代ｌ縺ｰfalse
     */
    static bool AABBToCapsule(const AABBCollider&    aabb,    VECTOR posA,
                               const CapsuleCollider& capsule, VECTOR posC);

private:
    // 繧､繝ｳ繧ｹ繧ｿ繝ｳ繧ｹ蛹也ｦ∵ｭ｢
    Collision3D() = delete;
};
