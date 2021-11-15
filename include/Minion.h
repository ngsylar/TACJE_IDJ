#ifndef MINION_H
#define MINION_H

#include "Component.h"

class Minion: public Component {
    private:
        std::weak_ptr<GameObject> alienCenter;
        float arc;

    public:
        Minion(
            GameObject& associated,
            GameObject& alienCenter,
            float arcOffsetDeg=0
        );
        void Update(float dt);
        void Render();
        bool Is(std::string type);
        void Shoot(Vec2 target);
};

#endif