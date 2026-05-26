//ボール関係のヘッダーファイル
#pragma once
#include "Player.h"
#include <DxLib.h>

//ボール関係の定数
/** @brief ボールの初期X座標の定数 */
static constexpr float BALL_X = 640.0f;
/** @brief ボールの初期Y座標の定数 */
static constexpr float BALL_Y = 360.0f;
/** @brief ボールの初期X方向への速度の定数 */
static constexpr float BALL_SPPED_X = 5.0f;
/** @brief ボールの初期Y方向への速度の定数 */
static constexpr float BALL_SPPED_Y = 3.0f;
/** @brief ボールの速度上限の定数 */
static constexpr float BALL_MAX_SPEED = 15.0f;
/** @brief ボールの直径の定数 */
static constexpr int BALL_SIZE = 20;

class Ball
{
public:
    Ball(float x, float y, float sx, float sy, int size);

    bool Update();
    void Draw();

    void ReflectFromPlayer(const Player& player);
    void ReflectFromBlock();
    void ReflectFromPaddle(const VECTOR& normal);

    float GetX() const { return ballX_; }
    float GetY() const { return ballY_; }
    int GetSize() const { return ballSize_; }

private:
    /** @brief ボールのX座標 */
    float ballX_;

    /** @brief ボールのY座標 */
    float ballY_;

    /** @brief ボールのX方向への移動速度 */
    float ballSpeedX_;

    /** @brief ボールのY方向への移動速度 */
    float ballSpeedY_;

    /** @brief ボールの大きさ */
    int ballSize_;
};