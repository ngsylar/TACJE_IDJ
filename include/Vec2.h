#ifndef VEC2_H
#define VEC2_H

class Vec2 {
    public:
        float x, y;

        Vec2();
        Vec2(float x, float y);
        float Magnitude();
        float Angle(Vec2 target);
        float Distance(Vec2 target);
        Vec2 Direction(float angle);
        
        void Normalize();
        Vec2 Rotate(float angle);

        Vec2 operator+(const Vec2& vec);
        Vec2 operator-(const Vec2& vec);
        Vec2 operator*(const float& scalar);

        Vec2& operator=(const Vec2& vec);
        Vec2& operator+=(const Vec2& vec);
        Vec2& operator-=(const Vec2& vec);
        Vec2& operator*=(const float& scalar);
};

#endif