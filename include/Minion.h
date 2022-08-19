#ifndef MINION_H
#define MINION_H

#include "Component.h"

#define MINION_SPRITE                   "assets/img/minion.png"
#define MINION_ARC_DISTANCE             120.0f, 0.0f
#define MINION_ARC_SPEED                0.25f
#define MINION_SCALE_MIN                0.66f
#define MINION_SCALE_MAX                1.06f
#define MINION_HP_MODIFIER              20
#define MINION_ANGLEDEG_ADJUST          -90.0f

#define MINION_BULLET_SPRITE            "assets/img/minionbullet2.png"
#define MINION_BULLET_FRAME_COUNT       3
#define MINION_BULLET_FRAME_TIME        0.04f
#define MINION_BULLET_SPEED             600.0f
#define MINION_BULLET_DAMAGE            10
#define MINION_BULLET_TARGETS_PLAYER    true

class Minion: public Component {
    private:
        std::weak_ptr<GameObject> alienCenter;
        float arc;
        int hp;
    
    public:
        Minion(
            GameObject& associated,
            GameObject& alienCenter,
            float arcOffsetDeg=0.0f
        );
        void Update(float dt);
        void Render();
        void Shoot(Vec2 target);
        Vec2 GetPosition();
        void NotifyCollision(GameObject& other);
        bool IsDead();
        bool Is(std::string type);
};

#endif