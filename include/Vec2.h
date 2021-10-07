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
        void Normalize();

        Vec2 operator+(const Vec2& vec);
        Vec2 operator-(const Vec2& vec);
        Vec2 operator*(const float& scalar);
        Vec2& operator=(const Vec2& vec);
        Vec2& operator+=(const Vec2& vec);
        Vec2& operator-=(const Vec2& vec);
        Vec2& operator*=(const float& scalar);
};

#endif