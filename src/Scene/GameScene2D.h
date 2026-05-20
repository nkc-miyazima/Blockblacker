#pragma once
#include "BaseScene.h"
#include "Player.h"
#include "Ball.h"
#include "Paddle.h"
#include "ParticleManager.h"
#include "BallTrailManager.h"
#include <DxLib.h>
#include <vector>

/**
 * @brief 2Dゲーム本編を表すシーンクラス
 *
 * 矢印キーでプレイヤーを動かし、アイテムを取得するシンプルな2Dゲーム
 * このシーンをクリアするとGameScene3Dへ遷移
 */
class GameScene2D : public BaseScene
{
public:
    Player player_;
    Ball ball_;
    BlockManager blockmanager_;
    Paddle paddle_;
    ParticleManager particle_;
    BallTrailManager balltrail_;

    /**
     * @brief 2Dゲームシーンを生成
     * @param sceneManager シーン遷移を依頼する先のマネージャー
     * @return なし。
     */
    explicit GameScene2D(SceneManager* sceneManager);

    /**
     * @brief 2Dゲームシーンを破棄
     * @return なし。
     */
    ~GameScene2D() override;

    /**
     * @brief 2Dゲームシーンの初期化
     * @return なし。
     */
    void Init() override;

    /**
     * @brief 2Dゲームシーンの更新処理
     * @return なし。
     */
    void Update() override;

    /**
     * @brief 2Dゲームシーンの描画処理
     * @return なし。
     */
    void Draw() override;

    int GetScore() { return lastscore_; }
    int GetLives() { return lastlives_; }
    int GetBrestime() { return blockrestime_; }

private:
    /** @brief スコアを管理する変数 */
    int score_ = 0;

    /** @brief プレイヤーのライフが0になったらtrueになる */
    bool isGameOver_ = false;

    /** @brief プレイヤーの残りライフ数を管理する変数 */
    int lives_ = INIT_LIVES;

    /** @brief 残り時間*/
    float timer_ = 60;

    /** @brief フレームカウント*/
    int time_ = 0;

    /** @brief プレイヤーがダメージを受けて無敵状態になる時の無敵時間の残り時間*/
    int playerInvincibletime_ = 0;

    int bg = LoadGraph("assets/png/HAI.png");
    int lastlives_;
    int lastscore_;
    int blockrestime_;
};
