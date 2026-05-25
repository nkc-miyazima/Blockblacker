//プレイヤー関係のヘッダーファイル
#pragma once
#include "Block.h"

/** @brief プレイヤーの初期X座標の定数 */
static constexpr float PLAYER_X = 540.0f;
/** @brief プレイヤーの初期Y座標の定数 */
static constexpr float PLAYER_Y = 650.0f;
/** @brief プレイヤーの速度の定数 */
static constexpr float PLAYER_SPPED = 6.0f;
/** @brief プレイヤーの大きさの定数 */
static constexpr int PLAYER_SIZE = 50;

class Player
{
public:
    Player() : playerX_(0), playerY_(0), playerSpeed_(0), playerSize_(0) {}
    Player(float x, float y, float speed, int size);

    void ResolveCollision(const BlockManager::Block& block);
    void Update();
    void Draw();

    void SetSpeedMultiplier(float m) { speedMultiplier_ = m; }
    float GetX() const { return playerX_; }
    float GetY() const { return playerY_; }
    float GetSpeed() const { return playerSpeed_; }
    int   GetSize() const { return playerSize_; }

private:
    /** @brief プレイヤーのX座標 */
    float playerX_;

    /** @brief プレイヤーのY座標 */
    float playerY_;

    /** @brief プレイヤーの移動速度 */
    float playerSpeed_;

    /** @brief プレイヤーの大きさ */
    int playerSize_;

    /** @brief プレイヤーの速度倍率 */
    float speedMultiplier_ = 1;
};
