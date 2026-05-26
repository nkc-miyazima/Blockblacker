#pragma once
#include "BaseScene.h"
#include "../GameObject/.h/Player.h"
#include "../GameObject/.h/ball.h"
#include "../GameObject/.h/Paddle.h"
#include "ParticleManager.h"
#include "../GameObject/.h/BallTrailManager.h"
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
    enum class GameMode {
        Basic,
        Endless,
        // 後でちょっと追加するかも
    };

    /**
     * @brief 2Dゲームシーンを生成
     * @param sceneManager シーン遷移を依頼する先のマネージャー
     * @return なし。
     */
    explicit GameScene2D(SceneManager* sceneManager, GameMode mode);

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
    int GetBrestime() { return blockrestime_; }

private:
    GameMode mode_;
    Player player_;
    Ball ball_;
    BlockManager blockmanager_;
    Paddle paddle_;
    ParticleManager particle_;
    BallTrailManager balltrail_;

    /** @brief スコアを管理する変数 */
    int score_ = 0;

    /** @brief 最終スコアを管理してリザルトに伝える変数 */
    int lastscore_;

    /** @brief ブロックが全消しされて復活した回数をカウントする変数 */
    int blockrestime_;

    /** @brief プレイヤーのライフが0になったらtrueになる */
    bool isGameOver_ = false;

    /** @brief エネルギー*/
    //float energy_;

    /** @brief プレイヤーがボールと接触した時にめり込んだりして連続ヒットを起こすのを防止する為の無敵時間の残り時間*/
    int playerInvincibletime_ = 0;

    /** @brief 背景の読み込み*/
    int bg = LoadGraph("assets/png/HAI.png");

    /** @brief エンドレスモード用のライフ*/
    int life_ = 3;
};
