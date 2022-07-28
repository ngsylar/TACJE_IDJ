#ifndef MINION_H
#define MINION_H

#include "Component.h"

#define MINION_SPRITE           "assets/img/minion.png"
#define MINION_ARC_DISTANCE     120, 0
#define MINION_ARC_SPEED        0.25f
#define MINION_SCALE_MIN        0.66f
#define MINION_SCALE_MAX        1.06f
#define MINION_ANGLEDEG_ADJUST  270.0f

class Minion: public Component {
    private:
        std::weak_ptr<GameObject> alienCenter;
        float arc;
    
    public:
        Minion(
            GameObject& associated,
            GameObject& alienCenter,
            float arcOffsetDeg=0.0f
        );
        void Update(float dt);
        void Render();
        bool Is(std::string type);
        void Shoot(Vec2 target);
        Vec2 GetPosition();
};

#endif