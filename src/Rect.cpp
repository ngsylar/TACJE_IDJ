#include "Rect.h"

Rect::Rect () {
    x = 0;
    y = 0;
    w = 0;
    h = 0;
}

Rect::Rect (float x, float y, float w, float h) {
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

bool Rect::Contains (float pX, float pY) {
    return ((pX > x) and (pX < (x+w)) and (pY > y) and (pY < (y+h)));
}

Vec2 Rect::GetCenter () {
    return Vec2(x+w/2, y+h/2);
}