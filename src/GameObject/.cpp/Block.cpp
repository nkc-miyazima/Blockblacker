#include "../.h/Block.h"
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
            blocks_[i].maxhp = 1 + res / 3;
            if (blocks_[i].maxhp > 10)
            {
                blocks_[i].maxhp = 9;       //ブロックの最大耐久値は9
            }
            blocks_[i].hp = blocks_[i].maxhp;
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

bool BlockManager::DamageBlock(int index, int damage)
{
    blocks_[index].hp -= damage;
    if (blocks_[index].hp <= 0)
    {
        blocks_[index].active = false;
        return true; // 壊れた
    }
    return false; // まだ生きてる
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
        switch (blocks_[i].hp)
        {
        case 1:     //赤色になる
            blocks_[i].r = 255;
            blocks_[i].g = 0;
            blocks_[i].b = 0;
            break;
        case 2:     //緑色になる
            blocks_[i].r = 0;
            blocks_[i].g = 255;
            blocks_[i].b = 0;
            break;
        case 3:     //青色になる
            blocks_[i].r = 0;
            blocks_[i].g = 0;
            blocks_[i].b = 255;
            break;
        case 4:     //オレンジっぽくなる
            blocks_[i].r = 245;
            blocks_[i].g = 255;
            blocks_[i].b = 0;
            break;
        case 5:
            blocks_[i].r = 255;
            blocks_[i].g = 0;
            blocks_[i].b = 255;
            break;
        case 6:
            blocks_[i].r = 0;
            blocks_[i].g = 255;
            blocks_[i].b = 255;
            break;
        case 7:
            blocks_[i].r = 50;
            blocks_[i].g = 50;
            blocks_[i].b = 50;
            break;
        case 8:
            blocks_[i].r = 150;
            blocks_[i].g = 150;
            blocks_[i].b = 150;
            break;
        case 9:
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