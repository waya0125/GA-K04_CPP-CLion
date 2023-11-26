//
// Created by waya on 2023/06/10.
// Updated on 2023/10/20.
//
#ifndef VECTOR_H
#define VECTOR_H

//## 環境に応じて設定
#pragma once
using namespace std;
#include <cmath>
#include <iostream>

/// <summary>##### 2次元ベクトルクラス #####</summary><br>
/// # できること<br>
/// <param>Vector2(float x, float y)</param>: Vector2構造体のインスタンスを作成<br>
/// <param>float x, y: Vector2構造体のインスタンスのx, y座標を設定・取得<br>
/// 参考文献 : なし<br>
/// 注意     : なし
class Vector2 {
public:
    // x, yの値を保持する変数
    float x, y;

    // コンストラクタ & デストラクタ
    // なおコンストラクタにexplicitをつけると暗黙の型変換ができなくなるため現状はつけない。
    Vector2(float x = 0, float y = 0) : x(x), y(y) {
        cout << "calling constructor." << endl;
    }
    ~Vector2() {
        cout << "calling destructor." << endl;
    }

    // x, yの値を設定する関数
    [[nodiscard]]
    inline float X() const {
        return x;
    }
    inline float X(float d) {
        return this->x = d;
    }
    [[nodiscard]]
    inline float Y() const {
        return y;
    }
    inline float Y(float d) {
        return this->y = d;
    }
};

#endif //VECTOR_H