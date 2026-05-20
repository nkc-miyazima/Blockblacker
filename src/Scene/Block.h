#pragma once

/** @brief ブロックのX方向の配置する数の定数 */
static constexpr int BLOCK_COLS = 7;
/** @brief ブロックのY方向の配置する数の定数 */
static constexpr int BLOCK_ROWS = 4;
/** @brief ブロックの総配置数の定数 */
static constexpr int BLOCK_COUNT = BLOCK_COLS * BLOCK_ROWS;
/** @brief ブロックの横幅の定数 */
static constexpr int BLOCK_W = 160;
/** @brief ブロックの縦幅の定数 */
static constexpr int BLOCK_H = 40;
/** @brief ブロック一個目の初期位置のX座標の定数 */
static constexpr float BLOCK_START_X = 60.0f;
/** @brief ブロック一個目の初期位置のY座標の定数 */
static constexpr float BLOCK_START_Y = 80.0f;
/** @brief ブロック同士の配置間隔のX方向の定数 */
static constexpr int BLOCK_GAP_X = 5;
/** @brief ブロック同士の配置間隔のY方向の定数 */
static constexpr int BLOCK_GAP_Y = 5;
/** @brief ブロック一個あたりの破壊時に得られるスコアの定数 */
static constexpr int BLOCK_SCORE = 100;

class BlockManager 
{
public:
    void Init(int res);
    void Draw();

    bool IsAllCleared() const;

    //ブロックの構造体
    struct Block
    {
        /** @brief ブロックの左上のX座標 */
        float x = 0.0f;
        /** @brief ブロックの左上のY座標 */
        float y = 0.0f;
        int r = 255;    //赤系
        int g = 255;    //緑系
        int b = 255;    //青系
        /** @brief ブロックが壊れているかどうか　true:破壊済,false:未破壊 */
        bool active = false;
    };

    Block* GetBlocks() { return blocks_; }
    void BreakBlock(int index)
    {
        blocks_[index].active = false;
    }

private:
    /** @brief ブロックを配列に定義 */
    Block blocks_[BLOCK_COUNT];
};