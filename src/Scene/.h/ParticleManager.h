#pragma once
#include <vector>
//パーティクル系統用のヘッダーファイル

struct Particle {
    float x, y;
    float vx, vy;
    int life;
    int maxLife = life;
    int color;
    float size;
    bool isRing;
};

class ParticleManager {
public:
    void Add(float x, float y, float vx, float vy, int life, int color);
    void SpawnPaddleEffect(float cx, float cy);
    void SpawnReflectRing(float x, float y);
    void Update();
    void Draw();

private:
    std::vector<Particle> particles_;
};
