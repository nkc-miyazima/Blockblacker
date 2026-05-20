#include "Common/Constants.h"
#include "Input/InputManager.h"
#include "Scene/SceneManager.h"

#include <DxLib.h>

/**
 * @brief ゲームのエントリーポイントです。
 * @return 正常終了時は0、初期化失敗時は-1です。
 */
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    SetOutApplicationLogValidFlag(FALSE);
    ChangeWindowMode(TRUE);
    SetGraphMode(Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT, 32);
    SetMainWindowText(Constants::WINDOW_TITLE);

    if (DxLib_Init() == -1)
    {
        return -1;
    }

    // 3D描画に必要なZバッファを有効にします。
    // これがないと奥行き順に正しく描画されません。
    SetUseZBuffer3D(TRUE);
    SetWriteZBuffer3D(TRUE);

    // 3Dライティングを有効にします。
    SetUseLighting(TRUE);

    SetDrawScreen(DX_SCREEN_BACK);

    SceneManager sceneManager;
    sceneManager.ChangeScene(SceneID::Title);

    while (ProcessMessage() == 0)
    {
        // フレームの先頭で入力状態を更新する。
        InputManager::GetInstance().Update();

        // どのシーンからでもESCキーでゲームを終了する。
        if (InputManager::GetInstance().IsKeyPressed(KEY_INPUT_ESCAPE))
        {
            break;
        }

        // シーンのロジック更新を行う。
        sceneManager.Update();

        // 画面を消去してから現在シーンを描画する。
        ClearDrawScreen();
        sceneManager.Draw();

        ScreenFlip();

        // 簡易的なFPS制御でCPU使用率を抑える。
        WaitTimer(1000 / Constants::TARGET_FPS);
    }

    DxLib_End();
    return 0;
}
