#ifndef GA_04_CPP_CLION_OPTION_H
#define GA_04_CPP_CLION_OPTION_H

#define WIDTH 1280
#define HEIGHT 720
#define PI 3.14F
#define COUNTOF(array) (sizeof(array) / sizeof(array[0])) // 配列の要素数をカウントする. Powered by KOBAYASHI Atsuki.

unsigned int white = GetColor(255,255,255);
unsigned int red = GetColor(255,0,0);
unsigned int black = GetColor(0,0,0);
int circleState = 0;

float Distance2(Vector2 v1, Vector2 v2) {
    Vector2 v3 = {v1.X() - v2.X(), v1.Y() - v2.Y()};
    if((v1.x - v2.x) > 0) {
        return sqrt(v3.X() * v3.X() + v3.Y() * v3.Y());
    } else {
        return -sqrt(v3.X() * v3.X() + v3.Y() * v3.Y());
    }
}

#endif //GA_04_CPP_CLION_OPTION_H
