#include "Vec2.h"

Vec2::Vec2 () {
    x = 0;
    y = 0;
}

Vec2::Vec2 (int x, int y) {
    this->x = x;
    this->y = y;
}

Vec2 Vec2::GetRotated (float theta) {
    return Vec2(x*cos(theta)-y*sin(theta), y*cos(theta)-x*sin(theta)); 
}

Vec2 Vec2::operator+ (const Vec2& vec) {
    return Vec2(x+vec.x, y+vec.y);
}

Vec2 Vec2::operator- (const Vec2& vec) {
    return Vec2(x-vec.x, y-vec.y);
}