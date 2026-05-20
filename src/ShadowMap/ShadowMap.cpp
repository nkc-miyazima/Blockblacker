#include "ShadowMap.h"

ShadowMap::ShadowMap()
    : shadowMapHandle_(-1)
{
}

ShadowMap::~ShadowMap()
{
    Finalize();
}

bool ShadowMap::Init(int width, int height)
{
    shadowMapHandle_ = MakeShadowMap(width, height);
    return shadowMapHandle_ != -1;
}

void ShadowMap::Finalize()
{
    if (shadowMapHandle_ != -1)
    {
        DeleteShadowMap(shadowMapHandle_);
        shadowMapHandle_ = -1;
    }
}

void ShadowMap::SetLightDirection(VECTOR dir)
{
    if (shadowMapHandle_ == -1)
    {
        return;
    }

    SetShadowMapLightDirection(shadowMapHandle_, dir);
}

void ShadowMap::SetArea(VECTOR center, float range)
{
    if (shadowMapHandle_ == -1)
    {
        return;
    }

    // 繝ｩ繧､繝医′蠖ｱ髻ｿ縺吶ｋ繝ｯ繝ｼ繝ｫ繝臥ｩｺ髢謎ｸ翫・遽・峇繧定ｨｭ螳・
    SetShadowMapDrawArea(shadowMapHandle_,
        VGet(center.x - range, center.y - range, center.z - range),
        VGet(center.x + range, center.y + range, center.z + range));
}

void ShadowMap::BeginDraw()
{
    if (shadowMapHandle_ == -1)
    {
        return;
    }

    // 繧ｷ繝｣繝峨え繝槭ャ繝励∈縺ｮ謠冗判繝｢繝ｼ繝峨↓蛻・ｊ譖ｿ縺・
    ShadowMap_DrawSetup(shadowMapHandle_);
}

void ShadowMap::EndDraw()
{
    if (shadowMapHandle_ == -1)
    {
        return;
    }

    // 繧ｷ繝｣繝峨え繝槭ャ繝励∈縺ｮ謠冗判繝｢繝ｼ繝峨ｒ邨ゆｺ・
    ShadowMap_DrawEnd();
}

void ShadowMap::Apply()
{
    if (shadowMapHandle_ == -1)
    {
        return;
    }

    // 繧ｷ繝｣繝峨え繝槭ャ繝励ｒ譛牙柑蛹悶＠縺ｦ繧ｷ繝ｼ繝ｳ謠冗判譎ゅ↓蠖ｱ縺瑚誠縺｡繧九ｈ縺・↓
    SetUseShadowMap(0, shadowMapHandle_);
}

void ShadowMap::Clear()
{
    // -1 繧呈ｸ｡縺吶％縺ｨ縺ｧ繧ｹ繝ｭ繝・ヨ0縺ｮ繧ｷ繝｣繝峨え繝槭ャ繝励・菴ｿ逕ｨ繧定ｧ｣髯､
    SetUseShadowMap(0, -1);
}
