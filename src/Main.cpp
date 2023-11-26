// 以下の行がないとコンパイルが通りません
#pragma comment(linker, "/subsystem:windows")

//## 環境に応じて設定
using namespace std; // std名前空間を使用
#include "DxLib.h"   // DXライブラリ
#include "Vector.h"  // ベクトルクラス
#include "Circle.h"  // 円クラス
#include "Utils.h"   // ユーティリティ (秘伝のタレ)
#include "Option.h"  // その他設定

// プログラムの最初はWinMainで始める
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    //##### 初期設定 #####//
    ChangeWindowMode(TRUE); // ウィンドウモード設定
    SetGraphMode(WIDTH, HEIGHT, 32); // 画面サイズ設定
    SetWaitVSyncFlag(TRUE); // 垂直同期を有効にする

    float wireAngle = 0.0F; // 十字を書かないといけないらしい

    // DXライブラリ初期化処理
    if(DxLib_Init() == -1) {
        return -1; // エラーが起きたら直ちに終了
    }

    // 円の初期化
    CircleManager circle[2] {
        CircleManager(Vector2(200, HEIGHT / 1.2), 25),
        CircleManager(Vector2(WIDTH / 2, HEIGHT / 1.2), 50)
        //CircleManager(Vector2(WIDTH - 200, HEIGHT / 1.2), 50)
    };

    //##### メインループ（描画処理） #####//
    while(ProcessMessage() == 0) {
        ClearDrawScreen(); // 画面の更新

        printfDx("Hello World!");

        // 今操作している円の過去座標に現在座標を書き込む
        circle[circleState].posPrevious = circle[circleState].posNow;

        // キーに入力があれば移動処理
        // Left or A
        if(CheckHitKey(KEY_INPUT_LEFT) || CheckHitKey(KEY_INPUT_A)) {
            circle[circleState].posNow.x -= 5;
        }
        // Right or D
        if(CheckHitKey(KEY_INPUT_RIGHT) || CheckHitKey(KEY_INPUT_D)) {
            circle[circleState].posNow.x += 5;
        }

        // 円の描画と移動・計算などなど
        for(int i = 0; i < COUNTOF(circle); i++) {
            // 今操作している円に色々やる
            if(circleState == i) {
                // 相対座標を取り出す
                circle[i].distance = getVectorDistanceSign(circle[i].posNow, circle[i].posPrevious);

                // 角速度を取り出す
                circle[i].angularVelocity = PI * circle[i].distance / (circle[i].R() * PI);

                // 累積角度に角速度を加算する
                circle[i].cumulativeAngle += circle[i].angularVelocity;

                //
                circle[i].posVectorEnd = circle[i].posNow;
            }

            // 円の中に線を描画するよ
            for (int j = 0; j < 2 * COUNTOF(circle); j++) {
                // 基準線より上に描画したいので補正する
                circle[i].posNow.y -= circle[i].R();

                // 末端座標
                circle[i].posVectorEnd.x = circle[i].posNow.X() + (sin(circle[i].cumulativeAngle + wireAngle) * circle[i].R());
                circle[i].posVectorEnd.y = circle[i].posNow.Y() + (cos(circle[i].cumulativeAngle + wireAngle) * circle[i].R());

                // 十字線の描画
                DrawLine(circle[i].posNow.X(), circle[i].posNow.Y(), circle[i].posVectorEnd.X(), circle[i].posVectorEnd.Y(), white);

                // 補正して計算したので元に戻す
                circle[i].posNow.y += circle[i].R();

                // 末端を中央座標に
                circle[i].posVectorEnd = circle[i].posNow;

                // 角度の更新
                wireAngle += 1.57F;
            }

            // 角度の初期化
            wireAngle = 0.0F;
        }

        // 接触しましたか？
        for(int i = 0; i < COUNTOF(circle); i++) {
            // 当たっていたら続行
            if(circleState == i) continue;
            // 接触したら
            if(hitCheck(circle[i].posNow, circle[i].R(), circle[!i].posNow, circle[!i].R())) {
                // 今操作している円を変更する 0, 1, 2 ... と対応できるようにする。
                circleState = i;
                //circleState = !circleState;

                // 今操作している円の色を変更する
                circle[i].hit = true;
                break;
            }
            else {
                // 今操作している円の色を変更する
                circle[i].hit = false;
            }
        }

        // 描画しましょう
        for(int i = 0; i < COUNTOF(circle); i++) {
            // 接触している円の色を変更する
            if(circle[i].hit)
                DrawCircle(circle[i].posNow.X(), circle[i].posNow.Y() - circle[i].R(), circle[i].R(), red, FALSE);
            else
                DrawCircle(circle[i].posNow.X(), circle[i].posNow.Y() - circle[i].R(), circle[i].R(), white, FALSE);
        }

        // 基準線
        DrawLine(0, HEIGHT / 1.2, WIDTH, HEIGHT / 1.2, white);

        //Sleep(10); // 遅延させる

        // 画面の更新（必須）
        ScreenFlip(); // 画面を反転させる処理
        clsDx();      // デバッグログ画面をクリアする処理
    }

    DxLib_End(); // DX Libraryの使用を終了する処理
    return 0;    // ソフトを正常終了
}