#include "Player.h"
#include "Paddle.h"
#include "InputManager.h"
#include "Constants.h"
#include <DxLib.h>

Player::Player(float x, float y, float speed, int size)
    : playerX_(x), playerY_(y), playerSpeed_(speed), playerSize_(size)
{
}

void Player::ResolveCollision(const BlockManager::Block& block)
{
    //後で使う変数の初期化
    float minOverlap = -1;

    //プレイヤーの四隅の座標
    float px1 = playerX_;
    float py1 = playerY_;
    float px2 = playerX_ + playerSize_;
    float py2 = playerY_ + playerSize_;

    //ブロックの四隅の座標
    float bx1 = block.x;
    float by1 = block.y;
    float bx2 = block.x + BLOCK_W;
    float by2 = block.y + BLOCK_H;

    // 重なり量
    float overlapLeft = px2 - bx1; // プレイヤー右 → ブロック左
    float overlapRight = bx2 - px1; // ブロック右 → プレイヤー左
    float overlapTop = py2 - by1; // プレイヤー下 → ブロック上
    float overlapBottom = by2 - py1; // ブロック下 → プレイヤー上

    //上記四つの中で最小の値を調べ、minOverlapに代入
    if (overlapLeft <= overlapRight) 
    {
        if (overlapLeft <= overlapTop)
        {
            if (overlapLeft <= overlapBottom) 
            {
                minOverlap = overlapLeft;
            }
            else
            {
                minOverlap = overlapBottom;
            }
        }
        else
        {
            if (overlapTop <= overlapBottom)
            {
                minOverlap = overlapTop;
            }
            else
            {
                minOverlap = overlapBottom;
            }
        }
    }
    else
    {
        if (overlapRight <= overlapTop)
        {
            if (overlapRight <= overlapBottom)
            {
                minOverlap = overlapRight;
            }
            else
            {
                minOverlap = overlapBottom;
            }
        }
        else
        {
            if (overlapTop <= overlapBottom)
            {
                minOverlap = overlapTop;
            }
            else
            {
                minOverlap = overlapBottom;
            }
        }
    }

    if (minOverlap == overlapLeft)
    {
        // 左から押し戻す
        playerX_ = bx1 - playerSize_;
    }
    else if (minOverlap == overlapRight)
    {
        // 右から押し戻す
        playerX_ = bx2;
    }
    else if (minOverlap == overlapTop)
    {
        // 上から押し戻す
        playerY_ = by1 - playerSize_;
    }
    else if (minOverlap == overlapBottom)
    {
        // 下から押し戻す
        playerY_ = by2;
    }
}

void Player::Update()
{
    float speed = playerSpeed_ * speedMultiplier_;
    // 矢印キーが押されている間、プレイヤーを上下左右に移動
    InputManager& input = InputManager::GetInstance();
    if (input.IsKeyHeld(KEY_INPUT_LEFT) || input.IsKeyHeld(KEY_INPUT_A))
    {
        playerX_ -= speed;
    }
    if (input.IsKeyHeld(KEY_INPUT_RIGHT) || input.IsKeyHeld(KEY_INPUT_D))
    {
        playerX_ += speed;
    }
    if (input.IsKeyHeld(KEY_INPUT_UP) || input.IsKeyHeld(KEY_INPUT_W))
    {
        playerY_ -= speed;
    }
    if (input.IsKeyHeld(KEY_INPUT_DOWN) || input.IsKeyHeld(KEY_INPUT_S))
    {
        playerY_ += speed;
    }

    //範囲制御(画面外に行けないようにする)
    //左端
    if (playerX_ < 0.0f)
    {
        playerX_ = 0.0f;
    }
    //上端
    if (playerY_ < 0.0f) 
    {
        playerY_ = 0.0f;
    }

    //比較や代入に使うために変数に切り出す
    const int maxX = static_cast<float>(Constants::SCREEN_WIDTH - playerSize_);
    const int maxY = static_cast<float>(Constants::SCREEN_HEIGHT - playerSize_);
    //右端
    if (playerX_ > maxX)
    {
        playerX_ = maxX;
    }
    //下端
    if (playerY_ > maxY)
    {
        playerY_ = maxY;
    }
}

void Player::Draw()
{
    // プレイヤーは円形として描画
    DrawBox(
        static_cast<int>(playerX_),
        static_cast<int>(playerY_),
        static_cast<int>(playerX_ + playerSize_),
        static_cast<int>(playerY_ + playerSize_),
        GetColor(255, 255, 255),
        TRUE
    );
}