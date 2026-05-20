#include "Block.h"
#include <DxLib.h>

void BlockManager::Init(int res)
{
    //ブロックを横BLOCK_COLS列×縦BLOCK_ROWS行に初期化
    for (int row = 0;row < BLOCK_ROWS;++row)
    {
        for (int col = 0;col < BLOCK_COLS;++col)
        {
            int r = 70 + res * 5;
            int i = row * BLOCK_COLS + col;
            blocks_[i].x = BLOCK_START_X + static_cast<float>(col * (BLOCK_W + BLOCK_GAP_X));
            blocks_[i].y = BLOCK_START_Y + static_cast<float>(row * (BLOCK_H + BLOCK_GAP_Y));
            if (r <= 95) 
            {
                blocks_[i].active = (rand() % 100 < r);
            }
            else 
            {
                blocks_[i].active = (rand() % 100 < 95);
            }
        }
    }
}

bool BlockManager::IsAllCleared() const
{
    for (int i = 0; i < BLOCK_COUNT; ++i)
    {
        if (blocks_[i].active)
        {
            return false;
        }
    }
    return true;
}

void BlockManager::Draw()
{
    //activeなブロックだけ描画
    for (int i = 0;i < BLOCK_COUNT;++i) {
        if (!blocks_[i].active) { continue; }
        //行番号を計算
        int row = i / BLOCK_COLS;
        switch (row)
        {
        case 0:     //赤色になる
            blocks_[i].r = 255;
            blocks_[i].g = 0;
            blocks_[i].b = 0;
            break;
        case 1:     //緑色になる
            blocks_[i].r = 0;
            blocks_[i].g = 255;
            blocks_[i].b = 0;
            break;
        case 2:     //青色になる
            blocks_[i].r = 0;
            blocks_[i].g = 0;
            blocks_[i].b = 255;
            break;
        case 3:     //オレンジっぽくなる
            blocks_[i].r = 245;
            blocks_[i].g = 148;
            blocks_[i].b = 11;
            break;
        default:    //想定外の値が入ってくるなら一旦白色のブロックにする
            blocks_[i].r = 255;
            blocks_[i].g = 255;
            blocks_[i].b = 255;
            break;
        }
        DrawBox(
            static_cast<int>(blocks_[i].x),
            static_cast<int>(blocks_[i].y),
            static_cast<int>(blocks_[i].x) + BLOCK_W,
            static_cast<int>(blocks_[i].y) + BLOCK_H,
            GetColor(blocks_[i].r, blocks_[i].g, blocks_[i].b),
            TRUE);
    }
}