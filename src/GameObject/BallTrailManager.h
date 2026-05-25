#pragma once
#include <vector>
//ƒ{[ƒ‹‚Ì‹O“¹—p

struct BallTrail {
    float x, y;
    int life;
};

class BallTrailManager {
public:
    void Add(float x, float y);
    void Update();
    void Draw(int ballSize);

private:
    std::vector<BallTrail> trails_;
};
