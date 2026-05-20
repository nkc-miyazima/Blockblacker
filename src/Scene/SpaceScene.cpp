#include "SpaceScene.h"

#include "../Input/InputManager.h"
#include "../Primitive3D/Primitive3D.h"
#include "../Collision/Collision3D.h"
#include "SceneManager.h"

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <DxLib.h>

// ============================================================
// 螳壽焚
// ============================================================

/** @brief 閾ｪ蜍募燕騾ｲ騾溷ｺｦ (繝ｦ繝九ャ繝・遘・ */
static constexpr float PLAYER_SPEED       = 20.0f;
/** @brief 荳贋ｸ句ｷｦ蜿ｳ縺ｮ遘ｻ蜍暮溷ｺｦ (繝ｦ繝九ャ繝・遘・ */
static constexpr float PLAYER_MOVE_SPEED  = 8.0f;
/** @brief 遘ｻ蜍慕ｯ・峇縺ｮ蛻ｶ髯・*/
static constexpr float PLAYER_CLAMP       = 8.0f;
/** @brief 繝舌Φ繧ｯ蛯ｾ縺阪・螟牙喧騾溷ｺｦ (繝ｩ繧ｸ繧｢繝ｳ/遘・ */
static constexpr float PLAYER_TILT_SPEED  = 4.0f;
/** @brief 繝舌Φ繧ｯ縺ｮ譛螟ｧ隗貞ｺｦ (繝ｩ繧ｸ繧｢繝ｳ) */
static constexpr float PLAYER_TILT_MAX    = 0.6f;
/** @brief 繝舌Φ繧ｯ縺・縺ｫ謌ｻ繧矩溷ｺｦ (繝ｩ繧ｸ繧｢繝ｳ/遘・ */
static constexpr float PLAYER_TILT_RETURN = 6.0f;
/** @brief 閾ｪ讖溘・蠖薙◆繧雁愛螳夂帥蜊雁ｾ・*/
static constexpr float PLAYER_RADIUS      = 0.9f;

/** @brief 閾ｪ讖溘・繝・け繧ｹ縺ｮ繝上・繝輔し繧､繧ｺ */
static constexpr float SHIP_HX = 0.8f;
static constexpr float SHIP_HY = 0.4f;
static constexpr float SHIP_HZ = 1.2f;

/** @brief 蠑ｾ縺ｮ蜑埼ｲ騾溷ｺｦ (繝ｦ繝九ャ繝・遘・ */
static constexpr float BULLET_SPEED     = 50.0f;
/** @brief 蠑ｾ縺ｮ蠖薙◆繧雁愛螳夂帥蜊雁ｾ・*/
static constexpr float BULLET_RADIUS    = 0.3f;
/** @brief 蠑ｾ縺ｮ譛螟ｧ蟆・ｨ・(繝励Ξ繧､繝､繝ｼ縺九ｉ縺ｮ逶ｸ蟇ｾ霍晞屬) */
static constexpr float BULLET_MAX_RANGE = 60.0f;

/** @brief 蜷梧凾蜃ｺ迴ｾ縺吶ｋ髫懷ｮｳ迚ｩ縺ｮ逶ｮ讓呎焚 */
static constexpr int   OBSTACLE_COUNT       = 12;
/** @brief 髫懷ｮｳ迚ｩ縺ｮ繧ｹ繝昴・繝ｳ霍晞屬 (繝励Ξ繧､繝､繝ｼ蜑肴婿) */
static constexpr float OBSTACLE_SPAWN_DIST  = 80.0f;
/** @brief 繧ｹ繝昴・繝ｳ譎ゅ・繝ｩ繝ｳ繝繝Z謨｣蟶・㍼ */
static constexpr float OBSTACLE_SPAWN_SCATTER = 50.0f;
/** @brief 繧ｹ繝昴・繝ｳX遽・峇 (ﾂｱ) */
static constexpr float OBSTACLE_RANGE_X     = 9.0f;
/** @brief 繧ｹ繝昴・繝ｳY遽・峇 (ﾂｱ) */
static constexpr float OBSTACLE_RANGE_Y     = 7.0f;
/** @brief 縺薙・霍晞屬縺縺大ｾ梧婿縺ｫ騾壹ｊ驕弱℃縺滄囿螳ｳ迚ｩ繧貞炎髯､ */
static constexpr float OBSTACLE_REMOVE_DIST = 5.0f;

/** @brief 蛻晄悄繝ｩ繧､繝墓焚 */
static constexpr int   INITIAL_LIVES     = 3;
/** @brief 繧ｲ繝ｼ繝縺ｮ蛻ｶ髯先凾髢・(遘・ */
static constexpr float GAME_DURATION_SEC = 60.0f;
/** @brief 繧ｲ繝ｼ繝邨ゆｺ・ｾ後↓繝ｪ繧ｶ繝ｫ繝磯・遘ｻ縺吶ｋ縺ｾ縺ｧ縺ｮ蠕・ｩ滓凾髢・(遘・ */
static constexpr float END_WAIT_SEC      = 2.0f;

/** @brief 繧ｰ繝ｪ繝・ラ縺ｮ邱夐俣髫・(繝ｦ繝九ャ繝・ */
static constexpr float GRID_SPACING = 6.0f;
/** @brief 迚・・縺ｮ繧ｰ繝ｪ繝・ラ邱壽悽謨ｰ */
static constexpr int   GRID_COUNT   = 8;
/** @brief 繧ｰ繝ｪ繝・ラ縺ｮY蠎ｧ讓・*/
static constexpr float GRID_Y       = -5.0f;

/** @brief 蝗ｺ螳壹ョ繝ｫ繧ｿ繧ｿ繧､繝 (遘・ */
static constexpr float DELTA_TIME = 1.0f / 60.0f;

// ============================================================
// 繝輔ぃ繧､繝ｫ繝ｭ繝ｼ繧ｫ繝ｫ繝倥Ν繝代・髢｢謨ｰ
// ============================================================

/**
 * @brief 閾ｪ讖溘ｒ蝗櫁ｻ｢縺輔○縺溘Ρ繧､繝､繝ｼ繝輔Ξ繝ｼ繝繝懊ャ繧ｯ繧ｹ縺ｨ縺励※謠冗判
 * @param pos    閾ｪ讖溘・繝ｯ繝ｼ繝ｫ繝牙ｺｧ讓・
 * @param tiltX  X霆ｸ繝舌Φ繧ｯ隗・(繝ｩ繧ｸ繧｢繝ｳ)
 * @param tiltZ  Z霆ｸ繝舌Φ繧ｯ隗・(繝ｩ繧ｸ繧｢繝ｳ)
 */
static void DrawPlayerShip(VECTOR pos, float tiltX, float tiltZ)
{
    // 繝ｭ繝ｼ繧ｫ繝ｫ蠎ｧ讓咏ｳｻ縺ｧ縺ｮ繝懊ャ繧ｯ繧ｹ8鬆らせ
    VECTOR v[8] =
    {
        VGet(-SHIP_HX,  SHIP_HY, -SHIP_HZ),
        VGet( SHIP_HX,  SHIP_HY, -SHIP_HZ),
        VGet( SHIP_HX,  SHIP_HY,  SHIP_HZ),
        VGet(-SHIP_HX,  SHIP_HY,  SHIP_HZ),
        VGet(-SHIP_HX, -SHIP_HY, -SHIP_HZ),
        VGet( SHIP_HX, -SHIP_HY, -SHIP_HZ),
        VGet( SHIP_HX, -SHIP_HY,  SHIP_HZ),
        VGet(-SHIP_HX, -SHIP_HY,  SHIP_HZ),
    };

    // 繝舌Φ繧ｯ蝗櫁ｻ｢蠕後↓繝ｯ繝ｼ繝ｫ繝臥ｧｻ蜍輔ｒ驕ｩ逕ｨ
    const MATRIX mat = MMult(
        MMult(MGetRotX(tiltX), MGetRotZ(tiltZ)),
        MGetTranslate(pos));
    for (int i = 0; i < 8; i++) { v[i] = VTransform(v[i], mat); }

    const unsigned int c = GetColor(0, 255, 128); // 譏弱ｋ縺・ｷ・

    // 荳企擇
    DrawLine3D(v[0], v[1], c); DrawLine3D(v[1], v[2], c);
    DrawLine3D(v[2], v[3], c); DrawLine3D(v[3], v[0], c);
    // 荳矩擇
    DrawLine3D(v[4], v[5], c); DrawLine3D(v[5], v[6], c);
    DrawLine3D(v[6], v[7], c); DrawLine3D(v[7], v[4], c);
    // 邵ｦ霎ｺ
    DrawLine3D(v[0], v[4], c); DrawLine3D(v[1], v[5], c);
    DrawLine3D(v[2], v[6], c); DrawLine3D(v[3], v[7], c);
}

// ============================================================
// SpaceScene 繝｡繝ｳ繝舌・髢｢謨ｰ
// ============================================================

SpaceScene::SpaceScene(SceneManager* sceneManager)
    : BaseScene(sceneManager)
    , playerPos_(VGet(0.0f, 0.0f, 0.0f))
    , playerTiltX_(0.0f)
    , playerTiltZ_(0.0f)
    , lives_(INITIAL_LIVES)
    , startTime_(0)
    , isGameOver_(false)
    , isClear_(false)
    , endTimer_(0.0f)
    , deltaTime_(DELTA_TIME)
{
}

SpaceScene::~SpaceScene() = default;

void SpaceScene::Init()
{
    // 蜈ｨ迥ｶ諷九・繝ｪ繧ｻ繝・ヨ
    playerPos_   = VGet(0.0f, 0.0f, 0.0f);
    playerTiltX_ = 0.0f;
    playerTiltZ_ = 0.0f;
    lives_       = INITIAL_LIVES;
    startTime_   = GetNowCount();
    isGameOver_  = false;
    isClear_     = false;
    endTimer_    = 0.0f;
    bullets_.clear();
    obstacles_.clear();

    // 繧ｫ繝｡繝ｩ繧定・讖溘・蠕梧婿荳頑婿縺ｫ驟咲ｽｮ
    camera_.Follow(playerPos_, VGet(0.0f, 3.0f, -10.0f));
    camera_.Update();

    // 蛻晄悄髫懷ｮｳ迚ｩ繧偵せ繝昴・繝ｳ
    SpawnObstaclesIfNeeded();
}

void SpaceScene::Update()
{
    // --- 邨ゆｺ・憾諷九・蜃ｦ逅・---
    // 繝｡繝・そ繝ｼ繧ｸ繧定｡ｨ遉ｺ縺吶ｋ髢薙∝ｰ代＠蠕・▲縺ｦ縺九ｉ繧ｷ繝ｼ繝ｳ驕ｷ遘ｻ
    if (isGameOver_ || isClear_)
    {
        endTimer_ += deltaTime_;
        if (endTimer_ >= END_WAIT_SEC)
        {
            sceneManager_->ChangeScene(SceneID::Result);
        }
        return;
    }

    // --- 繧ｿ繧､繝槭・ ---
    const float elapsed   = static_cast<float>(GetNowCount() - startTime_) / 1000.0f;
    const float remaining = GAME_DURATION_SEC - elapsed;

    if (remaining <= 0.0f) { isClear_   = true; return; }
    if (lives_     <= 0)   { isGameOver_ = true; return; }

    // --- 繧ｫ繝｡繝ｩ霑ｽ蠕・---
    camera_.Follow(playerPos_, VGet(0.0f, 3.0f, -10.0f));
    camera_.Update();

    // --- 閾ｪ蜍募燕騾ｲ ---
    playerPos_.z += PLAYER_SPEED * deltaTime_;

    // --- 蜈･蜉帛・逅・---
    InputManager& input = InputManager::GetInstance();

    const bool moveLeft  = input.IsKeyHeld(KEY_INPUT_LEFT);
    const bool moveRight = input.IsKeyHeld(KEY_INPUT_RIGHT);
    const bool moveUp    = input.IsKeyHeld(KEY_INPUT_UP);
    const bool moveDown  = input.IsKeyHeld(KEY_INPUT_DOWN);

    if (moveLeft)  { playerPos_.x -= PLAYER_MOVE_SPEED * deltaTime_; }
    if (moveRight) { playerPos_.x += PLAYER_MOVE_SPEED * deltaTime_; }
    if (moveUp)    { playerPos_.y += PLAYER_MOVE_SPEED * deltaTime_; }
    if (moveDown)  { playerPos_.y -= PLAYER_MOVE_SPEED * deltaTime_; }

    // XY菴咲ｽｮ縺ｮ繧ｯ繝ｩ繝ｳ繝・
    if (playerPos_.x >  PLAYER_CLAMP) playerPos_.x =  PLAYER_CLAMP;
    if (playerPos_.x < -PLAYER_CLAMP) playerPos_.x = -PLAYER_CLAMP;
    if (playerPos_.y >  PLAYER_CLAMP) playerPos_.y =  PLAYER_CLAMP;
    if (playerPos_.y < -PLAYER_CLAMP) playerPos_.y = -PLAYER_CLAMP;

    // --- 繝舌Φ繧ｯ蛯ｾ縺阪・譖ｴ譁ｰ ---
    // 蟾ｦ蜿ｳ蜈･蜉・ Z霆ｸ蛯ｾ縺・
    if (moveLeft)       { playerTiltZ_ += PLAYER_TILT_SPEED  * deltaTime_; }
    else if (moveRight) { playerTiltZ_ -= PLAYER_TILT_SPEED  * deltaTime_; }
    else
    {
        // 蜈･蜉帙↑縺・ 0縺ｫ蜷代°縺｣縺ｦ閾ｪ蜍募ｾｩ蟶ｰ
        if (playerTiltZ_ > 0.0f) { playerTiltZ_ -= PLAYER_TILT_RETURN * deltaTime_; if (playerTiltZ_ < 0.0f) playerTiltZ_ = 0.0f; }
        if (playerTiltZ_ < 0.0f) { playerTiltZ_ += PLAYER_TILT_RETURN * deltaTime_; if (playerTiltZ_ > 0.0f) playerTiltZ_ = 0.0f; }
    }
    // 荳贋ｸ句・蜉・ X霆ｸ蛯ｾ縺・
    if (moveUp)        { playerTiltX_ -= PLAYER_TILT_SPEED  * deltaTime_; }
    else if (moveDown) { playerTiltX_ += PLAYER_TILT_SPEED  * deltaTime_; }
    else
    {
        if (playerTiltX_ > 0.0f) { playerTiltX_ -= PLAYER_TILT_RETURN * deltaTime_; if (playerTiltX_ < 0.0f) playerTiltX_ = 0.0f; }
        if (playerTiltX_ < 0.0f) { playerTiltX_ += PLAYER_TILT_RETURN * deltaTime_; if (playerTiltX_ > 0.0f) playerTiltX_ = 0.0f; }
    }
    // 繝舌Φ繧ｯ隗偵・繧ｯ繝ｩ繝ｳ繝・
    if (playerTiltZ_ >  PLAYER_TILT_MAX) playerTiltZ_ =  PLAYER_TILT_MAX;
    if (playerTiltZ_ < -PLAYER_TILT_MAX) playerTiltZ_ = -PLAYER_TILT_MAX;
    if (playerTiltX_ >  PLAYER_TILT_MAX) playerTiltX_ =  PLAYER_TILT_MAX;
    if (playerTiltX_ < -PLAYER_TILT_MAX) playerTiltX_ = -PLAYER_TILT_MAX;

    // --- 繧ｹ繝壹・繧ｹ繧ｭ繝ｼ縺ｧ蠑ｾ繧堤匱蟆・---
    if (input.IsKeyPressed(KEY_INPUT_SPACE))
    {
        Bullet b;
        b.pos   = playerPos_;
        b.alive = true;
        bullets_.push_back(b);
    }

    // --- 蠑ｾ縺ｮ菴咲ｽｮ繧呈峩譁ｰ ---
    for (auto& b : bullets_)
    {
        if (b.alive) { b.pos.z += BULLET_SPEED * deltaTime_; }
    }

    // --- 蟆・ｨ句､悶∪縺溘・遐ｴ螢頑ｸ医∩縺ｮ蠑ｾ繧貞炎髯､ ---
    bullets_.erase(
        std::remove_if(bullets_.begin(), bullets_.end(),
            [&](const Bullet& b)
            {
                return !b.alive || b.pos.z > playerPos_.z + BULLET_MAX_RANGE;
            }),
        bullets_.end());

    // --- 蠕梧婿縺ｫ騾壹ｊ驕弱℃縺滄囿螳ｳ迚ｩ繧貞炎髯､ ---
    obstacles_.erase(
        std::remove_if(obstacles_.begin(), obstacles_.end(),
            [&](const Obstacle& o)
            {
                return !o.alive || o.pos.z < playerPos_.z - OBSTACLE_REMOVE_DIST;
            }),
        obstacles_.end());

    // 逶ｮ讓呎焚繧剃ｸ句屓縺｣縺ｦ縺・◆繧蛾囿螳ｳ迚ｩ繧定ｿｽ蜉繧ｹ繝昴・繝ｳ
    SpawnObstaclesIfNeeded();

    // --- 蠑ｾ縺ｨ髫懷ｮｳ迚ｩ縺ｮ陦晉ｪ∝愛螳・---
    for (auto& bullet : bullets_)
    {
        if (!bullet.alive) continue;
        for (auto& obs : obstacles_)
        {
            if (!obs.alive) continue;
            bool hit = false;
            if (obs.type == ObstacleType::Sphere)
            {
                hit = Collision3D::SphereToSphere(
                    SphereCollider(BULLET_RADIUS), bullet.pos,
                    SphereCollider(obs.sphereRadius), obs.pos);
            }
            else
            {
                hit = Collision3D::SphereToAABB(
                    SphereCollider(BULLET_RADIUS), bullet.pos,
                    AABBCollider(obs.boxHalf),     obs.pos);
            }
            if (hit)
            {
                obs.alive    = false;
                bullet.alive = false;
                break; // 1逋ｺ1繝偵ャ繝・
            }
        }
    }

    // --- 閾ｪ讖溘→髫懷ｮｳ迚ｩ縺ｮ陦晉ｪ∝愛螳・---
    for (auto& obs : obstacles_)
    {
        if (!obs.alive) continue;
        bool hit = false;
        if (obs.type == ObstacleType::Sphere)
        {
            hit = Collision3D::SphereToSphere(
                SphereCollider(PLAYER_RADIUS),    playerPos_,
                SphereCollider(obs.sphereRadius), obs.pos);
        }
        else
        {
            hit = Collision3D::SphereToAABB(
                SphereCollider(PLAYER_RADIUS), playerPos_,
                AABBCollider(obs.boxHalf),     obs.pos);
        }
        if (hit)
        {
            obs.alive = false;
            lives_--;
        }
    }

    // Enter繧ｭ繝ｼ繧呈款縺励◆迸ｬ髢薙↓繝ｪ繧ｶ繝ｫ繝育判髱｢縺ｸ驕ｷ遘ｻ
    if (InputManager::GetInstance().IsKeyPressed(KEY_INPUT_RETURN))
    {
        sceneManager_->ChangeScene(SceneID::Result);
    }
}

void SpaceScene::Draw()
{
    // 繧ｹ繧ｯ繝ｭ繝ｼ繝ｫ繧ｰ繝ｪ繝・ラ繧呈緒逕ｻ
    DrawGrid();

    // 閾ｪ讖溘ｒ謠冗判
    DrawPlayerShip(playerPos_, playerTiltX_, playerTiltZ_);

    // 蠑ｾ繧偵す繧｢繝ｳ縺ｮ繝ｯ繧､繝､繝ｼ繝輔Ξ繝ｼ繝逅・〒謠冗判
    const COLOR_U8 bulletColor = GetColorU8(0, 220, 255, 255);
    for (const auto& b : bullets_)
    {
        if (b.alive)
        {
            Primitive3D::DrawSphere(b.pos, BULLET_RADIUS, bulletColor, false);
        }
    }

    // 髫懷ｮｳ迚ｩ繧偵が繝ｬ繝ｳ繧ｸ縺ｮ繝ｯ繧､繝､繝ｼ繝輔Ξ繝ｼ繝縺ｧ謠冗判
    const COLOR_U8 obsColor = GetColorU8(255, 160, 0, 255);
    for (const auto& obs : obstacles_)
    {
        if (!obs.alive) continue;
        if (obs.type == ObstacleType::Sphere)
        {
            Primitive3D::DrawSphere(obs.pos, obs.sphereRadius, obsColor, false);
        }
        else
        {
            Primitive3D::DrawBox(
                VSub(obs.pos, obs.boxHalf),
                VAdd(obs.pos, obs.boxHalf),
                obsColor, false);
        }
    }

    // --- UI 繝・く繧ｹ繝・---
    const float elapsed   = static_cast<float>(GetNowCount() - startTime_) / 1000.0f;
    const float remaining = GAME_DURATION_SEC - elapsed;
    const float dispTime  = remaining > 0.0f ? remaining : 0.0f;

    DrawFormatString(10,  10, GetColor(255, 255, 255), "Lives: %d",      lives_);
    DrawFormatString(10,  40, GetColor(255, 255,   0), "Time:  %.0f s",  dispTime);
    DrawFormatString(10,  70, GetColor(180, 180, 255), "Space: Shoot | Arrows: Move", 0);

    if (isGameOver_)
    {
        DrawString(520, 340, "GAME OVER", GetColor(255, 60, 60));
    }
    else if (isClear_)
    {
        DrawString(545, 340, "CLEAR!",    GetColor(0, 255, 128));
    }
}

void SpaceScene::SpawnObstaclesIfNeeded()
{
    // OBSTACLE_COUNT 蛟九↓縺ｪ繧九∪縺ｧ髫懷ｮｳ迚ｩ繧偵せ繝昴・繝ｳ
    while (static_cast<int>(obstacles_.size()) < OBSTACLE_COUNT)
    {
        Obstacle obs;
        obs.alive = true;

        // 繝励Ξ繧､遽・峇蜀・〒繝ｩ繝ｳ繝繝縺ｪXY菴咲ｽｮ
        const float rx = static_cast<float>(rand() % 2001) / 1000.0f - 1.0f; // -1 ~ +1
        const float ry = static_cast<float>(rand() % 2001) / 1000.0f - 1.0f;
        obs.pos.x = rx * OBSTACLE_RANGE_X;
        obs.pos.y = ry * OBSTACLE_RANGE_Y;

        // 繝ｩ繝ｳ繝繝縺ｪ謨｣蟶・ｒ蜉縺医※蜑肴婿縺ｫ繧ｹ繝昴・繝ｳ
        const float scatter = static_cast<float>(rand() % static_cast<int>(OBSTACLE_SPAWN_SCATTER * 10)) / 10.0f;
        obs.pos.z = playerPos_.z + OBSTACLE_SPAWN_DIST + scatter;

        // 逅・°邂ｱ縺九ｒ繝ｩ繝ｳ繝繝縺ｫ豎ｺ螳・
        if (rand() % 2 == 0)
        {
            obs.type         = ObstacleType::Sphere;
            obs.sphereRadius = 0.8f + static_cast<float>(rand() % 13) / 10.0f; // 0.8 ~ 2.0
            obs.boxHalf      = VGet(1.0f, 1.0f, 1.0f); // 譛ｪ菴ｿ逕ｨ縺縺悟・譛溷喧
        }
        else
        {
            obs.type         = ObstacleType::Box;
            obs.sphereRadius = 1.0f; // 譛ｪ菴ｿ逕ｨ縺縺悟・譛溷喧
            const float bx = 0.7f + static_cast<float>(rand() % 14) / 10.0f; // 0.7 ~ 2.0
            const float by = 0.7f + static_cast<float>(rand() % 14) / 10.0f;
            const float bz = 0.7f + static_cast<float>(rand() % 14) / 10.0f;
            obs.boxHalf = VGet(bx, by, bz);
        }

        obstacles_.push_back(obs);
    }
}

void SpaceScene::DrawGrid() const
{
    const unsigned int col = GetColor(0, 100, 255);

    // 繝励Ξ繧､繝､繝ｼ縺ｮZ蠎ｧ讓吶ｒ繧ｰ繝ｪ繝・ラ髢馴囈縺ｧ繝｢繧ｸ繝･繝ｭ縺励※繧ｪ繝輔そ繝・ヨ險育ｮ・(繧ｷ繝ｼ繝繝ｬ繧ｹ縺ｪ繧ｹ繧ｯ繝ｭ繝ｼ繝ｫ)
    const float zOffset = fmodf(playerPos_.z, GRID_SPACING);

    for (int i = -GRID_COUNT; i <= GRID_COUNT; i++)
    {
        // Z譁ｹ蜷代・邵ｦ邱・
        const float x     = playerPos_.x + static_cast<float>(i) * GRID_SPACING;
        const float zNear = playerPos_.z - static_cast<float>(GRID_COUNT) * GRID_SPACING;
        const float zFar  = playerPos_.z + static_cast<float>(GRID_COUNT) * GRID_SPACING;
        DrawLine3D(VGet(x, GRID_Y, zNear), VGet(x, GRID_Y, zFar), col);

        // X譁ｹ蜷代・讓ｪ邱・(繝励Ξ繧､繝､繝ｼ縺ｫ蜷医ｏ縺帙※繧ｹ繧ｯ繝ｭ繝ｼ繝ｫ)
        const float z     = playerPos_.z + static_cast<float>(i) * GRID_SPACING - zOffset;
        const float xNear = playerPos_.x - static_cast<float>(GRID_COUNT) * GRID_SPACING;
        const float xFar  = playerPos_.x + static_cast<float>(GRID_COUNT) * GRID_SPACING;
        DrawLine3D(VGet(xNear, GRID_Y, z), VGet(xFar, GRID_Y, z), col);
    }
}
