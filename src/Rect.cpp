#include "GentooEngine.h"

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

Vec2 Rect::GetLocalCenter () {
    return Vec2(w/2.0f, h/2.0f);
}

Vec2 Rect::GetGlobalCenter () {
    return Vec2(x+w/2.0f, y+h/2.0f);
}

// remover
Vec2 Rect::GetCenter () {
    return Vec2(x+w/2.0f, y+h/2.0f);
}

void Rect::SetSize (float w, float h) {
    this->w = w;
    this->h = h;
}

void Rect::SetOffset (float oX, float oY) {
    offset = Vec2(oX, oY);
    SetPosition(GetGlobalCenter());
}

void Rect::SetOffset (Vec2 offset) {
    this->offset = offset;
    SetPosition(GetGlobalCenter());
}

void Rect::SetPosition (float pX, float pY) {
    x = (pX - w/2.0f) - offset.x;
    y = (pY - h/2.0f) - offset.y;
}

void Rect::SetPosition (Vec2 point) {
    x = (point.x - w/2.0f) - offset.x;
    y = (point.y - h/2.0f) - offset.y;
}

void Rect::Translate (Vec2 target) {
    x += target.x;
    y += target.y;
}

Vec2 Rect::GetPosition () {
    return (GetGlobalCenter() + offset);
}

bool Rect::Contains (float pX, float pY) {
    return ((pX > x) and (pX < (x+w)) and (pY > y) and (pY < (y+h)));
}