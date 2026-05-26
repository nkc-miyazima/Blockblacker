#include "../.h/Paddle.h"
#include <DxLib.h>

void Paddle::Init()
{
    paddlestate_ = None;
    paddleStart_ = VGet(0, 0, 0);
    paddleEnd_ = VGet(0, 0, 0);
}

void Paddle::StartDrawing(float x, float y)
{
    paddleStart_ = VGet(x, y, 0);
    paddleEnd_ = paddleStart_;
    paddlestate_ = Drawing;
}

void Paddle::FinishDrawing(float x, float y)
{
    paddleEnd_ = VGet(x, y, 0);
    paddlestate_ = Active;
}

void Paddle::Draw()
{
    if (paddlestate_ == None) return;
    DrawThickLine(paddleStart_, paddleEnd_, THICKNESS, GetColor(0, 255, 255));
}

void Paddle::DrawThickLine(VECTOR a, VECTOR b, float thickness, int color)
{
    VECTOR dir = VSub(b, a);        // 線分の方向
    VECTOR n = VNorm(VGet(-dir.y, dir.x, 0)); // 法線（90度回転）

    // 太さ分だけオフセット
    VECTOR offset = VScale(n, thickness / 2.0f);

    VECTOR p1 = VAdd(a, offset);
    VECTOR p2 = VSub(a, offset);
    VECTOR p3 = VAdd(b, offset);
    VECTOR p4 = VSub(b, offset);

    // 四角形として描画
    DrawTriangle((int)p1.x, (int)p1.y, (int)p2.x, (int)p2.y, (int)p3.x, (int)p3.y, color, TRUE);
    DrawTriangle((int)p2.x, (int)p2.y, (int)p3.x, (int)p3.y, (int)p4.x, (int)p4.y, color, TRUE);
}
