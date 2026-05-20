#include "GameScene3D.h"

#include "../Input/InputManager.h"
#include "../Primitive3D/Primitive3D.h"
#include "SceneManager.h"

#include <cmath>
#include <DxLib.h>

/** @brief 蠎翫・蜊雁ｹ・ｼ・譁ｹ蜷托ｼ・*/
static constexpr float FLOOR_HALF_WIDTH  = 5.0f;
/** @brief 蠎翫・蜊企ｫ倥＆・・譁ｹ蜷托ｼ・*/
static constexpr float FLOOR_HALF_HEIGHT = 0.25f;
/** @brief 蠎翫・蜊雁･･陦後″・・譁ｹ蜷托ｼ・*/
static constexpr float FLOOR_HALF_DEPTH  = 5.0f;
/** @brief 蠎翫・荳ｭ蠢ズ蠎ｧ讓・*/
static constexpr float FLOOR_CENTER_Y    = 0.0f;
/** @brief 逅・・蜊雁ｾ・*/
static constexpr float BALL_RADIUS       = 0.5f;
/** @brief 驥榊鴨蜉騾溷ｺｦ・医Θ繝九ャ繝・遘耽2・・*/
static constexpr float GRAVITY           = 9.8f;
/** @brief 豈弱ヵ繝ｬ繝ｼ繝縺ｮ騾溷ｺｦ貂幄｡ｰ菫よ焚・域束謫ｦ縺ｮ讓｡蛟｣・・*/
static constexpr float DAMPING           = 0.98f;
/** @brief 蠎翫・蛯ｾ縺埼溷ｺｦ・医Λ繧ｸ繧｢繝ｳ/遘抵ｼ・*/
static constexpr float TILT_SPEED        = 1.0f;
/** @brief 蠎翫・譛螟ｧ蛯ｾ縺崎ｧ抵ｼ育ｴ・0蠎ｦ・・*/
static constexpr float TILT_MAX          = DX_PI_F / 6.0f;

/**
 * @brief 蛯ｾ縺・◆蠎翫ｒ8鬆らせ繝懊ャ繧ｯ繧ｹ縺ｨ縺励※謠冗判
 * @param rotX X霆ｸ縺ｾ繧上ｊ縺ｮ蝗櫁ｻ｢隗抵ｼ医Λ繧ｸ繧｢繝ｳ・・ 謇句燕/螂･譁ｹ蜷代・蛯ｾ縺・
 * @param rotZ Z霆ｸ縺ｾ繧上ｊ縺ｮ蝗櫁ｻ｢隗抵ｼ医Λ繧ｸ繧｢繝ｳ・・ 蟾ｦ蜿ｳ譁ｹ蜷代・蛯ｾ縺・
 */
static void DrawTiltedFloor(float rotX, float rotZ)
{
    // 繝ｭ繝ｼ繧ｫ繝ｫ蠎ｧ讓吶〒縺ｮ蠎翫・繝・け繧ｹ8鬆らせ
    VECTOR v[8] =
    {
        VGet(-FLOOR_HALF_WIDTH,  FLOOR_HALF_HEIGHT, -FLOOR_HALF_DEPTH),
        VGet( FLOOR_HALF_WIDTH,  FLOOR_HALF_HEIGHT, -FLOOR_HALF_DEPTH),
        VGet( FLOOR_HALF_WIDTH,  FLOOR_HALF_HEIGHT,  FLOOR_HALF_DEPTH),
        VGet(-FLOOR_HALF_WIDTH,  FLOOR_HALF_HEIGHT,  FLOOR_HALF_DEPTH),
        VGet(-FLOOR_HALF_WIDTH, -FLOOR_HALF_HEIGHT, -FLOOR_HALF_DEPTH),
        VGet( FLOOR_HALF_WIDTH, -FLOOR_HALF_HEIGHT, -FLOOR_HALF_DEPTH),
        VGet( FLOOR_HALF_WIDTH, -FLOOR_HALF_HEIGHT,  FLOOR_HALF_DEPTH),
        VGet(-FLOOR_HALF_WIDTH, -FLOOR_HALF_HEIGHT,  FLOOR_HALF_DEPTH),
    };

    // X霆ｸ繝ｻZ霆ｸ縺ｮ蝗櫁ｻ｢陦悟・繧貞粋謌舌＠縺ｦ蜷・らせ縺ｫ驕ｩ逕ｨ
    const MATRIX mat = MMult(
        MMult(MGetRotX(rotX), MGetRotZ(rotZ)),
        MGetTranslate(VGet(0.0f, FLOOR_CENTER_Y, 0.0f)));
    for (int i = 0; i < 8; i++) { v[i] = VTransform(v[i], mat); }

    // 荳企擇繧偵・繝ｼ繧ｸ繝･濶ｲ縺ｧ謠冗判・井ｸ芽ｧ貞ｽ｢2譫夲ｼ・
    const unsigned int faceColor = GetColor(220, 200, 140);
    DrawTriangle3D(v[0], v[1], v[2], faceColor, TRUE);
    DrawTriangle3D(v[0], v[2], v[3], faceColor, TRUE);

    // 蛛ｴ髱｢繧貞ｰ代＠證励＞濶ｲ縺ｧ謠冗判・・髱｢ ﾃ・荳芽ｧ貞ｽ｢2譫夲ｼ・
    const unsigned int sideColor = GetColor(160, 140, 90);
    DrawTriangle3D(v[0], v[1], v[5], sideColor, TRUE);
    DrawTriangle3D(v[0], v[5], v[4], sideColor, TRUE);
    DrawTriangle3D(v[1], v[2], v[6], sideColor, TRUE);
    DrawTriangle3D(v[1], v[6], v[5], sideColor, TRUE);
    DrawTriangle3D(v[2], v[3], v[7], sideColor, TRUE);
    DrawTriangle3D(v[2], v[7], v[6], sideColor, TRUE);
    DrawTriangle3D(v[3], v[0], v[4], sideColor, TRUE);
    DrawTriangle3D(v[3], v[4], v[7], sideColor, TRUE);

    // 荳企擇縺ｮ霈ｪ驛ｭ繧帝ｻ偵＞邱壹〒謠冗判
    const unsigned int edgeColor = GetColor(40, 40, 40);
    DrawLine3D(v[0], v[1], edgeColor);
    DrawLine3D(v[1], v[2], edgeColor);
    DrawLine3D(v[2], v[3], edgeColor);
    DrawLine3D(v[3], v[0], edgeColor);
}

/**
 * @brief 繧ｳ繝ｳ繧ｹ繝医Λ繧ｯ繧ｿ
 */
GameScene3D::GameScene3D(SceneManager* sceneManager)
    : BaseScene(sceneManager)
    , floorRotX_(0.0f)
    , floorRotZ_(0.0f)
    , ballPos_(VGet(0.0f, FLOOR_CENTER_Y + FLOOR_HALF_HEIGHT + BALL_RADIUS, 0.0f))
    , ballVel_(VGet(0.0f, 0.0f, 0.0f))
    , deltaTime_(1.0f / 60.0f)
{
}

GameScene3D::~GameScene3D() = default;

/**
 * @brief 蛻晄悄蛹門・逅・
 */
void GameScene3D::Init()
{
    // 蠎翫・蛯ｾ縺阪→繝懊・繝ｫ縺ｮ迥ｶ諷九ｒ繝ｪ繧ｻ繝・ヨ
    floorRotX_ = 0.0f;
    floorRotZ_ = 0.0f;
    ballPos_   = VGet(0.0f, FLOOR_CENTER_Y + FLOOR_HALF_HEIGHT + BALL_RADIUS, 0.0f);
    ballVel_   = VGet(0.0f, 0.0f, 0.0f);

    light_.Init();

    // 蠎翫ｒ譁懊ａ荳翫°繧芽ｦ倶ｸ九ｍ縺吝崋螳壹き繝｡繝ｩ
    camera_.SetPosition(VGet(0.0f, 18.0f, -18.0f));
    camera_.SetTarget(VGet(0.0f, 0.0f, 0.0f));

    // 繧ｫ繝｡繝ｩ繧奪xLib縺ｫ蜿肴丐
    camera_.Update();
}

/**
 * @brief 豈弱ヵ繝ｬ繝ｼ繝縺ｮ譖ｴ譁ｰ蜃ｦ逅・
 */
void GameScene3D::Update()
{
    // 繧ｫ繝｡繝ｩ繧奪xLib縺ｫ蜿肴丐
    camera_.Update();

    InputManager& input = InputManager::GetInstance();

    // 荳贋ｸ九く繝ｼ: X霆ｸ縺ｾ繧上ｊ縺ｫ蠎翫ｒ蛯ｾ縺代※・域焔蜑・螂･譁ｹ蜷代・蛯ｾ縺搾ｼ・
    if (input.IsKeyHeld(KEY_INPUT_UP))    { floorRotX_ += TILT_SPEED * deltaTime_; }
    if (input.IsKeyHeld(KEY_INPUT_DOWN))  { floorRotX_ -= TILT_SPEED * deltaTime_; }

    // 蟾ｦ蜿ｳ繧ｭ繝ｼ: Z霆ｸ縺ｾ繧上ｊ縺ｫ蠎翫ｒ蛯ｾ縺托ｼ亥ｷｦ蜿ｳ譁ｹ蜷代・蛯ｾ縺搾ｼ・
    if (input.IsKeyHeld(KEY_INPUT_LEFT))  { floorRotZ_ += TILT_SPEED * deltaTime_; }
    if (input.IsKeyHeld(KEY_INPUT_RIGHT)) { floorRotZ_ -= TILT_SPEED * deltaTime_; }

    // 蛯ｾ縺鷹℃縺朱亟豁｢縺ｮ繧ｯ繝ｩ繝ｳ繝・
    if (floorRotX_ >  TILT_MAX) floorRotX_ =  TILT_MAX;
    if (floorRotX_ < -TILT_MAX) floorRotX_ = -TILT_MAX;
    if (floorRotZ_ >  TILT_MAX) floorRotZ_ =  TILT_MAX;
    if (floorRotZ_ < -TILT_MAX) floorRotZ_ = -TILT_MAX;

    // --- 繝懊・繝ｫ縺ｮ迚ｩ逅・す繝溘Η繝ｬ繝ｼ繧ｷ繝ｧ繝ｳ ---
    //
    // 蠎翫′蛯ｾ縺上→驥榊鴨縺ｮ荳驛ｨ縺悟ｺ企擇縺ｫ豐ｿ縺｣縺ｦ蜒阪″縲√・繝ｼ繝ｫ繧貞刈騾溘＆縺帙ｋ
    //
    //   X霆ｸ蛯ｾ縺・(floorRotX_) 竊・Z譁ｹ蜷代・隕九°縺代・驥榊鴨 = G * sin(rotX)
    //   Z霆ｸ蛯ｾ縺・(floorRotZ_) 竊・X譁ｹ蜷代・隕九°縺代・驥榊鴨 = G * sin(rotZ)

    ballVel_.x += -sinf(floorRotZ_) * GRAVITY * deltaTime_;
    ballVel_.z +=  sinf(floorRotX_) * GRAVITY * deltaTime_;

    // Y譁ｹ蜷代↓荳句髄縺阪・驥榊鴨繧呈ｯ弱ヵ繝ｬ繝ｼ繝蜉邂・
    ballVel_.y -= GRAVITY * deltaTime_;

    // 騾溷ｺｦ縺ｫ貂幄｡ｰ繧偵°縺代※霆｢縺後ｊ鞫ｩ謫ｦ繧貞・迴ｾ
    ballVel_.x *= DAMPING;
    ballVel_.z *= DAMPING;

    // 騾溷ｺｦ繧剃ｽ咲ｽｮ縺ｫ遨榊・
    ballPos_.x += ballVel_.x * deltaTime_;
    ballPos_.y += ballVel_.y * deltaTime_;
    ballPos_.z += ballVel_.z * deltaTime_;

    // --- 蠎企擇縺ｮY蠎ｧ讓吶ｒ險育ｮ・---
    //
    // 蠎翫・蟷ｳ髱｢繧湛霆ｸ繝ｻZ霆ｸ縺ｾ繧上ｊ縺ｫ蝗櫁ｻ｢縺輔○縺溘ｂ縺ｮ
    // 逅・・XZ菴咲ｽｮ縺ｫ縺翫￠繧句ｺ企擇縺ｮY蠎ｧ讓吶ｒ蟷ｳ髱｢譁ｹ遞句ｼ上°繧画ｱゅａ繧・
    //
    // 譛ｪ蝗櫁ｻ｢縺ｮ蠎翫・豕慕ｷ・ (0, 1, 0)
    // 蝗櫁ｻ｢蠕後・豕慕ｷ・ normal = rotMat * (0, 1, 0)
    //
    // 蟷ｳ髱｢譁ｹ遞句ｼ擾ｼ亥次轤ｹ騾夐℃・・
    //   normal.x * x + normal.y * y + normal.z * z = FLOOR_CENTER_Y
    //
    // 逅・・XZ菴咲ｽｮ縺ｧy繧定ｧ｣縺・
    //   y = (FLOOR_CENTER_Y - normal.x * x - normal.z * z) / normal.y
    const MATRIX rotMat   = MMult(MGetRotX(floorRotX_), MGetRotZ(floorRotZ_));
    const VECTOR normal   = VTransform(VGet(0.0f, 1.0f, 0.0f), rotMat);
    float floorSurfaceY   = FLOOR_CENTER_Y;
    if (fabsf(normal.y) > 0.001f)
    {
        floorSurfaceY = (FLOOR_CENTER_Y
                        - normal.x * ballPos_.x
                        - normal.z * ballPos_.z) / normal.y;
    }

    // 蠎翫・繝ｭ繝ｼ繧ｫ繝ｫ蠎ｧ讓咏ｳｻ縺ｫ螟画鋤縺吶ｋ縺溘ａ騾・屓霆｢陦悟・繧貞叙蠕・
    const MATRIX invRotMat = MMult(MGetRotZ(-floorRotZ_), MGetRotX(-floorRotX_));
    const VECTOR localPos  = VTransform(
        VGet(ballPos_.x, ballPos_.y, ballPos_.z),
        invRotMat);

    // 逅・′蠎翫・遽・峇蜀・↓縺ゅｋ縺句愛螳夲ｼ医Ο繝ｼ繧ｫ繝ｫ蠎ｧ讓吶〒縺ｮXZ蠅・阜繝√ぉ繝・け・・
    const bool onFloor = (fabsf(localPos.x) <= FLOOR_HALF_WIDTH &&
                          fabsf(localPos.z) <= FLOOR_HALF_DEPTH);

    // 逅・′蠎翫↓繧√ｊ霎ｼ繧薙〒縺・◆蝣ｴ蜷医∝ｺ企擇縺ｮ荳翫↓謚ｼ縺玲綾縺・
    // 蠎翫・遽・峇螟悶↑繧蛾㍾蜉帙〒閾ｪ逕ｱ關ｽ荳・
    if (onFloor)
    {
        const float contactY = floorSurfaceY + FLOOR_HALF_HEIGHT + BALL_RADIUS;
        if (ballPos_.y <= contactY)
        {
            ballPos_.y = contactY;
            ballVel_.y = 0.0f;
        }
    }

    // Enter繧ｭ繝ｼ繧呈款縺励◆迸ｬ髢薙↓繧ｹ繝壹・繧ｹ繧ｷ繝ｼ繝ｳ縺ｸ驕ｷ遘ｻ
    if (InputManager::GetInstance().IsKeyPressed(KEY_INPUT_RETURN))
    {
        sceneManager_->ChangeScene(SceneID::Space);
    }
}

/**
 * @brief 豈弱ヵ繝ｬ繝ｼ繝縺ｮ謠冗判蜃ｦ逅・
 */
void GameScene3D::Draw()
{
    // 蛯ｾ縺・◆蠎翫ｒ謠冗判
    DrawTiltedFloor(floorRotX_, floorRotZ_);

    // 逅・ｒ逋ｽ縺・｡励ｊ貎ｰ縺礼帥縺ｨ縺励※謠冗判
    Primitive3D::DrawSphere(ballPos_, BALL_RADIUS, GetColorU8(240, 20, 20, 255), true);

    DrawString(10, 10, "3D Rolling Ball",            GetColor(255, 255, 255));
    DrawString(10, 40, "Arrow Keys: Tilt the floor", GetColor(255, 255,   0));
}
