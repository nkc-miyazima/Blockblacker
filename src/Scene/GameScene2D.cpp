#include "GameScene2D.h"
#include "../Input/InputManager.h"
#include "../Collision/Collision2D.h"
#include "../Common/Constants.h"
#include "SceneManager.h"
#include <algorithm>
#include <cstdlib>
#include <DxLib.h>

/**
 * @brief 2Dゲームシーンの初期化
 * @return なし。
 */
void GameScene2D::Init()
{
    //ライフとか色々
    score_ = 0;                 //スコア
    lastscore_ = 0;
    isGameOver_ = false;        //ゲームオーバーフラグ
    blockrestime_ = 0;
    energy_ = 1000;
    paddle_.Init();
    blockmanager_.Init(blockrestime_);
}

/**
 * @brief 2Dゲームシーンを生成
 * @param sceneManager シーン遷移を依頼する先のマネージャー
 * @return なし。
 */
GameScene2D::GameScene2D(SceneManager* sceneManager)
    : BaseScene(sceneManager),
    player_(PLAYER_X, PLAYER_Y, PLAYER_SPPED, PLAYER_SIZE),
    ball_(BALL_X, BALL_Y, BALL_SPPED_X, BALL_SPPED_Y,BALL_SIZE),
    blockmanager_(),
    paddle_(){}

/**
 * @brief 2Dゲームシーンを破棄
 * @return なし。
 */
GameScene2D::~GameScene2D() = default;

/**
 * @brief 2Dゲームシーンの更新処理
 * @return なし。
 */
void GameScene2D::Update()
{
    bool reflected = ball_.Update();
    //インプット系を使うための定義
    InputManager& input = InputManager::GetInstance();

    //スペースキーを押すとパドルを書き始められる
    if (input.IsKeyPressed(KEY_INPUT_SPACE))
    {
        paddle_.StartDrawing(player_.GetX() + player_.GetSize() / 2, player_.GetY() + player_.GetSize() / 2);
    }

    //スペースキーを離すと書き始めた位置からパドルが描画される
    if (input.IsKeyReleased(KEY_INPUT_SPACE))
    {
        paddle_.FinishDrawing(player_.GetX() + player_.GetSize() / 2, player_.GetY() + player_.GetSize() / 2);
        VECTOR s = paddle_.GetPaddleStart();
        VECTOR e = paddle_.GetPaddleEnd();
        float cx = (s.x + e.x) * 0.5f;
        float cy = (s.y + e.y) * 0.5f;
        particle_.SpawnPaddleEffect(cx, cy);
    }

    //パドルを書いている間は動きが遅くなる
    if (paddle_.Getpaddlestate_() == Paddle::Drawing)
    {
        player_.SetSpeedMultiplier(0.5f);
    }
    else
    {
        player_.SetSpeedMultiplier(1.0f);
    }

    player_.Update();
    //ブロックの定義
    BlockManager::Block* b = blockmanager_.GetBlocks();
    for (int i = 0; i < BLOCK_COUNT; ++i)
    {
        if (!b[i].active) 
        {
            continue;
        }

        if (Collision2D::RectToRect(player_.GetX(), player_.GetY(), player_.GetSize(), player_.GetSize(),b[i].x, b[i].y, BLOCK_W, BLOCK_H))
        {
            // めり込んだので押し戻す
            player_.ResolveCollision(b[i]);
        }
    }

    //ボールの軌道関係
    balltrail_.Add(ball_.GetX() + ball_.GetSize() / 2,ball_.GetY() + ball_.GetSize() / 2);
    balltrail_.Update();

    //Collsion2Dを使ったプレイヤーとボールの当たり判定
    if (Collision2D::RectToRect(ball_.GetX(), ball_.GetY(), ball_.GetSize(), ball_.GetSize(), player_.GetX(), player_.GetY(), player_.GetSize(), player_.GetSize()))
    {
        ball_.ReflectFromPlayer(player_);
        if (playerInvincibletime_ == 0)
        {
            if (energy_ > 0)
            {
                energy_ -= 300;
            }
        }
        playerInvincibletime_ = 15;     //一度プレイヤーがボールに当たってから15フレームは無敵扱い
        reflected = true;
    }

    //Collsion2Dを使ったボールとブロックの当たり判定
    for (int i = 0;i < BLOCK_COUNT;++i) {
        if (!b[i].active) { continue; }
        if (Collision2D::RectToRect(ball_.GetX(), ball_.GetY(), ball_.GetSize(), ball_.GetSize(), b[i].x, b[i].y, BLOCK_W, BLOCK_H))
        {
            int plus = 200 - blockrestime_ * 40;
            blockmanager_.BreakBlock(i);
            ball_.ReflectFromBlock();
            score_ += BLOCK_SCORE;
            if (plus > 0) energy_ += plus;
            for (int k = 0; k < 15; k++)
            {
                float bx = b[i].x + BLOCK_W / 2;
                float by = b[i].y + BLOCK_H / 2;
                float vx = (rand() % 200 - 100) / 50.0f;
                float vy = (rand() % 200 - 100) / 50.0f;
                particle_.Add(bx, by, vx, vy, 30, GetColor(b[i].r, b[i].g, b[i].b));
            }
            reflected = true;
        }
    }
    
    //パドルとボールの当たり判定
    if (paddle_.Getpaddlestate_() == Paddle::Active)
    {
        VECTOR paddleStart_ = paddle_.GetPaddleStart();    //パドルの始点を記憶
        VECTOR paddleEnd_ = paddle_.GetPaddleEnd();        //パドルの終点を記憶
        VECTOR BallCenter = VGet(ball_.GetX() + ball_.GetSize() / 2, ball_.GetY() + ball_.GetSize() / 2, 0);      //ボールの中心を記憶

        VECTOR paddleVector = VSub(paddleEnd_, paddleStart_);         //パドルの方向ベクトル
        VECTOR Distance = VSub(BallCenter, paddleStart_);             //パドルとボールの距離

        //t:ボールからパドルへの垂線が、パドルのどの位置に落ちるかを 0〜1 で表した値。0未満または1より大きい場合パドルに当たっていない。
        float t = (Distance.x * paddleVector.x + Distance.y * paddleVector.y) / (paddleVector.x * paddleVector.x + paddleVector.y * paddleVector.y);
        t = std::clamp(t, 0.0f, 1.0f);      //クランプ

        VECTOR closest = VAdd(paddleStart_, VScale(paddleVector, t));        //ボールからパドルに下ろした垂線の足（最も近い点）
        VECTOR diff = VSub(BallCenter, closest);
        float dist = sqrtf(diff.x * diff.x + diff.y * diff.y);  //ボール中心とパドルの最短距離

        if (dist <= ball_.GetSize() / 2)        //ボールの中央とパドルの距離がボールの半径より短かったらパドルに当たっているとみなす     
        {
            //反射のためのあーだこーだ
            VECTOR normal = VNorm(VGet(-paddleVector.y, paddleVector.x, 0));
            ball_.ReflectFromPaddle(normal);
            reflected = true;
        }
    }

    if (reflected) 
    {
        particle_.SpawnReflectRing(ball_.GetX() + ball_.GetSize() / 2, ball_.GetY() + ball_.GetSize() / 2);
    }

    //ブロックが全消しされているなら
    if (blockmanager_.IsAllCleared())
    {
        blockrestime_++;
        blockmanager_.Init(blockrestime_);
    }

    //エネルギー減少
    if (energy_ > 0)
    {
        if (paddle_.Getpaddlestate_() == Paddle::Drawing) 
        {
            energy_--;
        }
        else 
        {
            energy_ -= 0.5f;
        }
        if (playerInvincibletime_ > 0) 
        {
            playerInvincibletime_--;
        }
    }

    //もしライフがなくなったら
    if (energy_ <= 0)
    {
        sceneManager_->lastScore = score_;
        isGameOver_ = true;     //ゲームオーバー表示に進む
    }

    particle_.Update();

    // Enterキーを押した瞬間にリザルトシーンへ遷移
    if (input.IsKeyPressed(KEY_INPUT_RETURN) || isGameOver_)
    {
        sceneManager_->ChangeScene(SceneID::Result);
    }
}

void DrawThickLine(VECTOR a, VECTOR b, float thickness, int color)
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

/**
 * @brief 2Dゲームシーンの描画処理
 * @return なし。
 */
void GameScene2D::Draw()
{
    DrawExtendGraph(0, 0, /*左上*/ 1280, 720, /* 右下（画面サイズ）*/bg, TRUE);
    //パドル
    paddle_.Draw();

    //ボールの軌道の描画
    balltrail_.Draw(ball_.GetSize());

    // ボール
    ball_.Draw();

    //プレイヤー
    player_.Draw();

    //ブロック
    blockmanager_.Draw();

    //パーティクル
    particle_.Draw();

    //UI表示
    //スコア
    DrawFormatString(Constants::SCREEN_WIDTH - 200, 10,GetColor(255, 255, 255),"SCORE: %d", score_);
    //エネルギー
    DrawFormatString(Constants::SCREEN_WIDTH - 400, 10,GetColor(255, 255, 0),"ENERGY: %.0f", energy_);

    // 次のシーンへの案内を表示
    DrawString(10, 40, "Press ENTER to resilt Scene", GetColor(255, 255, 0));
}
