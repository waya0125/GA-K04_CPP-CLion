#ifndef GA_04_CPP_CLION_CIRCLE_H
#define GA_04_CPP_CLION_CIRCLE_H

//## 環境に応じて設定
#pragma once
#include "DxLib.h"
#include "Vector.h"

/// <summary>##### 円クラス #####</summary><br>
/// # できること<br>
/// <param>Circle(Vector2 pos, float r)</param>: Circle構造体のインスタンスを作成<br>
/// <param>ONTOUCHCOLOR</param>: ポールにプレイヤーが触れている場合のサークルの色<br>
/// <param>UNTOUCHCOLOR</param>: ポールにプレイヤーが触れていない場合のサークルの色<br>
/// <param>PI</param>: 円周率<br>
/// <param>float radial</param>: 半径を設定・取得<br>
/// <param>float Distance</param>: 移動距離を設定・取得<br>
/// <param>float angularVelocity</param>: 角速度を設定・取得<br>
/// <param>float cumulativeAngle</param>: 累積角度を設定・取得<br>
/// <param>Vector2 posNow(float x, float y)</param>: 座標を設定・取得<br>
/// <param>Vector2 posPrevious(float x, float y)</param>: 前回の座標を設定・取得<br>
/// <param>Vector2 posVectorEnd(float x, float y)</param>: ベクトルの終点座標を設定・取得<br>
/// 参考文献 : なし<br>
/// 注意     : なし
class CircleManager {
public:
    bool hit = false;           // 接触しているかどうか
    float radial;               // 半径
    float distance = 0;         // 移動距離
    float angularVelocity = 0;  // 角速度
    float cumulativeAngle = 0;  // 累積角度
    Vector2 posNow;             // 座標
    Vector2 posPrevious;        // 前回の座標
    Vector2 posVectorEnd;       // ベクトルの終点座標

    // コンストラクタとデストラクタ
    CircleManager(Vector2 pos, float r) : posNow(pos), radial(r) {
        cout << "calling constructor." << endl;
    }
    ~CircleManager() {
        cout << "calling destructor." << endl;
    }

    [[nodiscard]]
    inline float R() const {
        return radial;
    }
    inline float R(float d) {
        return this->radial = d;
    }

    void Rolling();
};

void CircleManager::Rolling() {}

#endif //GA_04_CPP_CLION_CIRCLE_H
