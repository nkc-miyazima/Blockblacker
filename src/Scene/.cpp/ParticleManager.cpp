//パーティクル用のcppファイル
#include "ParticleManager.h"
#include <DxLib.h>

void ParticleManager::Add(float x, float y, float vx, float vy, int life, int color)
{
    Particle p;
    p.x = x;
    p.y = y;
    p.vx = vx;
    p.vy = vy;
    p.life = life;
    p.maxLife = life;
    p.size = 3.0f;     // 火花のサイズ
    p.color = color;
    p.isRing = false;  // 火花はリングじゃない
    particles_.push_back(p);
}

void ParticleManager::SpawnPaddleEffect(float cx, float cy)
{
    for (int k = 0; k < 50; k++)
    {
        float vx = (rand() % 200 - 100) / 50.0f;
        float vy = (rand() % 200 - 100) / 50.0f;
        int color = GetColor(200, 200, 255); // パドル用の青白い色

        Add(cx, cy, vx, vy, 40, color);
    }
}

void ParticleManager::SpawnReflectRing(float x, float y)
{
    for (int i = 0; i < 3; i++)
    {
        Particle p;
        p.x = x;
        p.y = y;
        p.vx = 0;
        p.vy = 0;
        p.life = 20 + i * 5;
        p.maxLife = p.life;
        p.size = 5 + i * 3; // 初期半径
        p.color = GetColor(180, 220, 255);
        p.isRing = true;
        particles_.push_back(p);
    }
}

void ParticleManager::Update()
{
    for (auto& p : particles_) {
        p.x += p.vx;
        p.y += p.vy;
        if (p.isRing) 
        {
            p.size += 1.5f; // フレームごとに半径拡大
        }
        p.life--;
    }
    particles_.erase(
        std::remove_if(particles_.begin(), particles_.end(),
            [](const Particle& p) { return p.life <= 0; }),
        particles_.end());
}

void ParticleManager::Draw()
{
    for (auto& p : particles_) {
        if (p.isRing) {

            float t = (float)p.life / (float)p.maxLife;
            int a = (int)(255 * t);

            // 色分解（GetColor2 は使わない）
            int r = (p.color >> 16) & 0xFF;
            int g = (p.color >> 8) & 0xFF;
            int b = p.color & 0xFF;

            // アルファ付きカラー
            int col = GetColor(r, g, b);

            // 中抜きリング
            DrawCircle((int)p.x, (int)p.y, (int)p.size, col, FALSE);
        }
        else {
            // 火花
            DrawBox((int)p.x, (int)p.y, (int)(p.x + 3), (int)(p.y + 3), p.color, TRUE);
        }
    }
}
