//ƒ{[ƒ‹‚Ì‹O“¹—p
#include "BallTrailManager.h"
#include <DxLib.h>

void BallTrailManager::Add(float x, float y)
{
    trails_.push_back({ x, y, 8 }); // õ–½‚ÍŒÅ’è‚Å‚àOK
}

void BallTrailManager::Update()
{
    for (auto& t : trails_) {
        t.life--;
    }

    trails_.erase(
        std::remove_if(trails_.begin(), trails_.end(),
            [](const BallTrail& t) { return t.life <= 0; }),
        trails_.end());
}

void BallTrailManager::Draw(int ballSize)
{
    for (const auto& t : trails_) {
        int alpha = t.life * 10 + 100;
        int col = GetColor(alpha, 0, 0);
        DrawCircle(t.x, t.y, ballSize / 2, col, TRUE);
    }
}
