#include "Vec2.h"

Vec2::Vec2 () {
    x = 0;
    y = 0;
}

Vec2::Vec2 (float x, float y) {
    this->x = x;
    this->y = y;
}

Vec2 Vec2::GetRotated (float theta) {
    return Vec2(x*cos(theta)-y*sin(theta), y*cos(theta)-x*sin(theta)); 
}

float Vec2::Magnitude () {
    return sqrt(x*x + y*y);
}

void Vec2::Normalize () {
    float magnitude = Magnitude();

    x /= magnitude;
    y /= magnitude;
}

Vec2 Vec2::operator+ (const Vec2& vec) {
    return Vec2(x+vec.x, y+vec.y);
}

Vec2 Vec2::operator- (const Vec2& vec) {
    return Vec2(x-vec.x, y-vec.y);
}

Vec2 Vec2::operator* (const float& scalar) {
    return Vec2(x*scalar, y*scalar);
}

Vec2& Vec2::operator= (const Vec2& vec) {
    x = vec.x;
    y = vec.y;
    return *this;
}

Vec2& Vec2::operator+= (const Vec2& vec) {
    x += vec.x;
    y += vec.y;
    return *this;
}

Vec2& Vec2::operator-= (const Vec2& vec) {
    x -= vec.x;
    y -= vec.y;
    return *this;
}

Vec2& Vec2::operator*= (const float& scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
}