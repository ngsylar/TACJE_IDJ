#include <cmath>

#include "Vec2.h"

Vec2::Vec2 () {
    x = 0;
    y = 0;
}

Vec2::Vec2 (float x, float y) {
    this->x = x;
    this->y = y;
}

float Vec2::Magnitude () {
    return sqrt(x*x + y*y);
}

float Vec2::Angle (Vec2 target) {
    return atan2(target.y-y, target.x-x);
}

float Vec2::Distance (Vec2 target) {
    target -= *this;
    return target.Magnitude();
}

Vec2 Vec2::Direction (float angle) {
    return Vec2(cos(angle), sin(angle));
}

void Vec2::Normalize () {
    float magnitude = Magnitude();

    x /= magnitude;
    y /= magnitude;
}

Vec2 Vec2::Rotate (float angle) {
    return Vec2(x*cos(angle)-y*sin(angle), y*cos(angle)-x*sin(angle)); 
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