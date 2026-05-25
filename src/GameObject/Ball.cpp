#include "Ball.h"
#include "Constants.h"
#include <DxLib.h>
#include <cmath>

Ball::Ball(float x, float y, float sx, float sy, int size)
    : ballX_(x), ballY_(y), ballSpeedX_(sx), ballSpeedY_(sy), ballSize_(size)
{
}

void Ball::ReflectFromPlayer(const Player& player)
{
    // 反射角度の計算
    float padCX = player.GetX() + player.GetSize() / 2.0f;
    float ballCX = ballX_ + ballSize_ / 2.0f;
    float diff = (ballCX - padCX) / (player.GetSize() / 2.0f);

    ballSpeedX_ = diff * ballSpeedX_;
    ballSpeedY_ *= -1.05f;

    //めり込み防止の押し出し処理

    // プレイヤー中心
    float px = player.GetX() + player.GetSize() / 2.0f;
    float py = player.GetY() + player.GetSize() / 2.0f;

    // ボール中心
    float bx = ballX_ + ballSize_ / 2.0f;
    float by = ballY_ + ballSize_ / 2.0f;

    // 押し出す方向（プレイヤー → ボール）
    float dx = bx - px;
    float dy = by - py;
    float len = sqrtf(dx * dx + dy * dy);

    if (len == 0) len = 0.01f; // 0除算防止

    dx /= len;
    dy /= len;

    // プレイヤー外側に押し出す距離
    float pushDist = (player.GetSize() / 2.0f) + (ballSize_ / 2.0f) + 1.0f;

    // ボールの位置を強制的に外側へ
    ballX_ = px + dx * pushDist - ballSize_ / 2.0f;
    ballY_ = py + dy * pushDist - ballSize_ / 2.0f;
}

void Ball::ReflectFromBlock()
{
    ballSpeedY_ *= -1.05f;
}

void Ball::ReflectFromPaddle(const VECTOR& normal)
{
    // 現在の速度ベクトル
    VECTOR v = VGet(ballSpeedX_, ballSpeedY_, 0);

    // 反射公式 R = V - 2(V・N)N
    float dot = v.x * normal.x + v.y * normal.y;
    VECTOR r = VSub(v, VScale(normal, 2.0f * dot));

    // 新しい速度を反映
    ballSpeedX_ = r.x;
    ballSpeedY_ = r.y;

    // めり込み防止のため少し押し出す（任意）
    if (fabs(ballSpeedX_) < 0.1f) ballSpeedX_ = (ballSpeedX_ >= 0 ? 0.1f : -0.1f);
    if (fabs(ballSpeedY_) < 0.1f) ballSpeedY_ = (ballSpeedY_ >= 0 ? 0.1f : -0.1f);

    // 少し加速（任意）
    ballSpeedX_ *= 1.05f;
    ballSpeedY_ *= 1.05f;
}

bool Ball::Update()
{
    bool reflected = false;
    ballX_ += ballSpeedX_;
    ballY_ += ballSpeedY_;

    // 画面端で反射
    if (ballX_ <= 0 || ballX_ + ballSize_ > Constants::SCREEN_WIDTH) 
    {
        ballSpeedX_ *= -1.05f;
        reflected = true;
    }

    if (ballY_ <= 0 || ballY_ + ballSize_ > Constants::SCREEN_HEIGHT)
    {
        ballSpeedY_ *= -1.05f;
        reflected = true;
    }

    // 速度制限
    if (ballSpeedX_ > BALL_MAX_SPEED) 
    {
        ballSpeedX_ = BALL_MAX_SPEED; 
    }
    if (ballSpeedX_ < -BALL_MAX_SPEED) 
    {
        ballSpeedX_ = -BALL_MAX_SPEED; 
    }
    if (ballSpeedY_ > BALL_MAX_SPEED) 
    {
        ballSpeedY_ = BALL_MAX_SPEED; 
    }
    if (ballSpeedY_ < -BALL_MAX_SPEED) 
    {
        ballSpeedY_ = -BALL_MAX_SPEED; 
    }

    return reflected;
}

void Ball::Draw()
{
    DrawCircle(
        (int)(ballX_ + ballSize_ / 2),
        (int)(ballY_ + ballSize_ / 2),
        ballSize_ / 2,
        GetColor(255, 0, 0),
        TRUE
    );
}
