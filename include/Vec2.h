#ifndef VEC2_H
#define VEC2_H

#include <cmath>

class Vec2 {
    public:
        float x, y;

        Vec2();
        Vec2(float x, float y);
        Vec2 GetRotated(float theta);
        float Magnitude();
        float AngleTo(Vec2 target);
        float DistanceTo(Vec2 target);
        Vec2 DirectionFrom(float angle);
        Vec2 Normalize();

        Vec2 operator+(const Vec2& vec);
        Vec2 operator-(const Vec2& vec);
        Vec2 operator*(const float& scalar);

        Vec2& operator+=(const Vec2& vec);
        Vec2& operator-=(const Vec2& vec);
        Vec2& operator*=(const float& scalar);
};

#endif