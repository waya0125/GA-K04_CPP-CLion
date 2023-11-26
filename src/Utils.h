//
// Created by waya on 2023/07/14.
// Updated on 2023/10/20.
//

#ifndef UTILS_CLASS
#define UTILS_CLASS

#pragma once
#include <cmath>
#include <iostream>
#include <random>
#include "Vector.h"
using namespace std;

// ##### ランダムな値を返却する関数 #####
// 参考文献 : http://vivi.dyndns.org/tech/cpp/random.html
// 引数     : min, max
// 戻り値   : min以上max以下のランダムな値
// 注意     : random関数を使用するため、randomをインクルードする必要がある
[[maybe_unused]]
int random(int min, int max) {
    random_device rnd;     // 非決定的な乱数生成器を生成
    mt19937 mt(rnd());     //  メルセンヌ・ツイスタの32ビット版、引数は初期シード値
    uniform_int_distribution<> rand100(min, max); // 範囲指定の乱数
    // ランダムな値を返却する
    return rand100(mt);
}

// ##### ベクトルの加算 #####
// 参考文献 : なし
// 引数     : V1, V2
// 戻り値   : 加算したVector2
// 注意     : なし
[[maybe_unused]]
Vector2 addVector(const Vector2& V1, const Vector2& V2) {
    // 加算したベクトルを計算
    Vector2 Result = {
            V1.x + V2.x,
            V1.y + V2.y
    };
    return Result;
}

// ##### ベクトルの減算 #####
// 参考文献 : なし
// 引数     : V1, V2
// 戻り値   : 減算したVector2
// 注意     : なし
[[maybe_unused]]
Vector2 subVector(const Vector2& V1, const Vector2& V2) {
    // 減算したベクトルを計算
    Vector2 Result = {
            V1.x - V2.x,
            V1.y - V2.y
    };
    return Result;
}

// ##### ベクトルの乗算 #####
// 参考文献 : なし
// 引数     : V1, V2
// 戻り値   : 乗算したベクトル
// 注意     : なし
[[maybe_unused]]
Vector2 mulVector(const Vector2& V1, const Vector2& V2) {
    // 乗算したベクトルを計算
    Vector2 Result = {
            V1.x * V2.x,
            V1.y * V2.y
    };
    return Result;
}

// ##### ベクトルの除算 #####
// 参考文献 : なし
// 引数     : V1, V2
// 戻り値   : 除算したベクトル
// 注意     : なし
[[maybe_unused]]
Vector2 divVector(const Vector2& V1, const Vector2& V2) {
    // 除算したベクトルを計算
    Vector2 Result = {
            V1.x / V2.x,
            V1.y / V2.y
    };
    return Result;
}

// ##### 外積計算関数 #####
// 参考文献 : ゲームアルゴリズム Z07 7ページ目資料
// 引数     : x1, y1, x2, y2
// 戻り値   : 外積計算されたfloat値
// 注意     : なし
[[maybe_unused]]
float crossProduct(const Vector2& V1, const Vector2& V2) {
    return V1.x * V2.y - V1.y * V2.x;
}

// ##### 内積計算関数 #####
// 参考文献 : ゲームアルゴリズム Z07 12ページ目資料
// 引数     : Vector2 V1, Vector2 V2
// 戻り値   : 内積計算されたfloat値
// 注意     : なし
[[maybe_unused]]
float dotProduct(const Vector2& V1, const Vector2& V2) {
    return V1.x * V2.x + V1.y * V2.y;
}

// ##### 相対ベクター計算関数 #####
// 参考文献 : ゲームアルゴリズム Z07 7ページ目資料
// 引数     : x1, y1, x2, y2
// 戻り値   : 相対ベクター
// 注意     : なし
[[maybe_unused]]
Vector2 relative(const Vector2& V1, const Vector2& V2) {
    // 2つの円の中心座標の差分を計算（相対ベクトル）
    return {V1.x - V1.y, V2.x - V2.y}; // 目的の地点 - 現在の地点
}

// ##### 2つの円の中心座標(Vector)の距離を計算する関数 #####
// 参考文献 : https://www.geisya.or.jp/~mwm48961/math/distance1j.htm
// 引数     : Vector2 V1, Vector2 V2
// 戻り値   : 2つの円の中心座標の距離
// 注意     : sqrt関数を使用するため、math.h or cmathをインクルードする必要がある
[[maybe_unused]]
float getVectorDistance(const Vector2& V1, const Vector2& V2) {
    // 2つの円の中心座標の差分を計算（相対ベクトル）
    Vector2 diff = subVector(V1, V2); // 目的の地点 - 現在の地点
    // 2つの円の中心座標の距離を計算
    return sqrtf(powf(diff.x, 2) + powf(diff.y, 2));
}

// ##### 2つの円の中心座標(Vector)の距離を計算して符号によって返す値を変える関数 #####
// 参考文献 : なし
// 引数     : Vector2 V1, Vector2 V2
// 戻り値   : 2つのポイント間の距離(float)
// 注意     : sqrt関数を使用するため、math.h or cmathをインクルードする必要がある
[[maybe_unused]]
float getVectorDistanceSign(const Vector2& V1, const Vector2& V2) {
    // 2つの円の中心座標の差分を計算（相対ベクトル）
    Vector2 diff = subVector(V1, V2); // 目的の地点 - 現在の地点
    // 2つの円の中心座標の距離を計算
    return sqrtf(powf(diff.x, 2) + powf(diff.y, 2)) * (diff.x < 0.0F ? 1.0F : -1.0F);
}

// ##### 相対ベクターの長さを計算する関数 #####
// 参考文献 : なし
// 引数     : Vector2 V1
// 戻り値   : 相対ベクターの長さ
// 注意     : sqrt関数を使用するため、math.h or cmathをインクルードする必要がある
[[maybe_unused]]
float getVectorLength(const Vector2& V1) {
    // 相対ベクトルの計算
    Vector2 relativeVector = mulVector(V1, V1);
    // 相対ベクトルの長さを計算
    return sqrtf(relativeVector.x + relativeVector.y);
}

// ##### 相対ベクター正規化 #####
// 参考文献 : ゲームアルゴリズム Z07 7ページ目資料
// 引数     : V1
// 戻り値   : 相対化されたVector2
// 注意     : なし
[[maybe_unused]]
static Vector2 normalized(const Vector2& V1) {
    // 正規化した相対ベクトルを計算
    Vector2 Result = {
            V1.x / sqrtf((V1.x * V1.x) + (V1.y * V1.y)),
            V1.y / sqrtf((V1.x * V1.x) + (V1.y * V1.y))
    };
    return Result;
}

// ##### 内積と外積を計算して点と点の間だったらtrueを返す #####
// 参考文献 : なし
// 引数     : Vector2 現在の座標, Vector2 地点A, Vector2 地点B
// 戻り値   : 点と点の間だったらtrue、そうでない場合はfalse
// 注意     : なし
[[maybe_unused]]
bool pointBetween(const Vector2& posV, const Vector2& V1, const Vector2& V2) {
    // 点と点の間かどうかを判定する
    // 2つの円の中心座標の差分を計算（相対ベクトル）
    // 目的の地点 - 現在の地点
    Vector2 Vs1 = subVector(V2, V1);     // 線分のベクトル
    Vector2 Vs2 = subVector(posV, V1);   // 点と線分の始点のベクトル
    Vector2 Vs3 = subVector(V1, V2);     // 線分のベクトル
    Vector2 Vs4 = subVector(posV, V2);   // 点と線分の終点のベクトル
    float   Vd1 = dotProduct(Vs1, Vs2);  // 内積
    float   Vd2 = dotProduct(Vs3, Vs4);  // 内積
    Vector2 Vn  = normalized(Vs1);       // 正規化
    float   Vc  = crossProduct(Vn, Vs2); // 外積

    // 点と点の間に侵入してきたらtrueを返す
    if (Vd1 > 0 && Vd2 > 0 && Vc >= 1) {
        return true;
    }

    return false;
}

// 判定処理を共通化
[[maybe_unused]]
Vector2 findDistance(const Vector2& V1, const Vector2& V2) {
    // 相対ベクトルを正規化
    Vector2 relativeVector = {
        (V1.x - V2.x) / getVectorDistance (V1, V2),
        (V1.y - V2.y) / getVectorDistance (V1, V2)
    };

    // 中央物体（球体）の進行方向ベクトルを返却
    return { relativeVector.y, -relativeVector.x };
}

// 当たり判定
[[maybe_unused]]
bool hitCheck(const Vector2& V1, const float& V1R, const Vector2& V2, const float& V2R) {
    // 2つの円の中心座標の距離を計算
    float distance = getVectorDistance(V1, V2);
    // 2つの円の半径の和を計算
    float sumR = V1R + V2R;
    // 2つの円の中心座標の距離が2つの円の半径の和より小さかったら
    if (distance < sumR) {
        // 当たっている
        return true;
    }
    // 当たっていない
    return false;
}

#endif //UTILS_CLASS