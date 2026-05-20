#include <DxLib.h>

class Paddle
{
public:

    enum PaddleState_ {
        None,
        Drawing,
        Active
    };
    PaddleState_ paddlestate_ = None;

    void Init();
    void StartDrawing(float x, float y);
    void FinishDrawing(float x, float y);
    void Draw();

    VECTOR GetPaddleStart() { return paddleStart_; }
    VECTOR GetPaddleEnd() { return paddleEnd_; }
    PaddleState_ Getpaddlestate_() { return paddlestate_; }

private:
    VECTOR paddleStart_;
    VECTOR paddleEnd_;

    static constexpr float THICKNESS = 6.0f;

    void DrawThickLine(VECTOR a, VECTOR b, float thickness, int color);
};
