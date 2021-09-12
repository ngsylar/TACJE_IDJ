#ifndef VEC2_H
#define VEC2_H

#include <cmath>

class Vec2 {
    public:
        float x, y;

        Vec2();
        Vec2(int x, int y);
        Vec2 GetRotated(float theta);
        Vec2 operator+(const Vec2& vec);
        Vec2 operator-(const Vec2& vec);
};

#endif