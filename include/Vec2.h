#ifndef VEC2_H
#define VEC2_H

class Vec2 {
    public:
        float x, y;

        Vec2();
        Vec2(float x, float y);
        Vec2 GetRotated(float theta);
        float Magnitude();
        float Angle (Vec2 vec);
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