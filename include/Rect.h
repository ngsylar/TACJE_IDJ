#ifndef RECT_H
#define RECT_H

#include "Vec2.h"

class Rect {
    public:
        float x, y, w, h;

        Rect();
        Rect(float x, float y, float w, float h);
        bool Contains(float pX, float pY);

        Vec2 GetCenter();
        void SetSize(float w, float h);
        void SetPosition(float x, float y);
        void SetPosition(Vec2 point);
        void Translate(Vec2 target);
};

#endif