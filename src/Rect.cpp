#include "Rect.h"
#include "Sprite.h"

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

void Rect::SetPosition (float pX, float pY) {
    x = pX - w/2;
    y = pY - h/2;
}

// void Rect::Translate (Vec2 dest, float dt) {
//     // float angle = Vec2(x,y).Angle(translation);
//     Vec2 trasnlation = Vec2(dest.x-x, dest.y-y);
//     trasnlation.Normalize();
//     x += dest.x * 2;
//     y += dest.y * 2;
// }