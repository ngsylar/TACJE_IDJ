#ifndef BULLET_H
#define BULLET_H

#include "Component.h"

#define MINION_BULLET_SPRITE            "assets/img/minionbullet2.png"
#define MINION_BULLET_SPEED             600.0f
#define MINION_BULLET_DAMAGE            10
#define MINION_BULLET_FRAME_COUNT       3
#define MINION_BULLET_FRAME_TIME        0.04f
#define MINION_BULLET_ANGLEDEG_ADJUST   0.0f

class Bullet: public Component {
    private:
        Vec2 speed;
        float distanceLeft;
        int damage;

    public:
        Bullet(
            GameObject& associated,
            std::string spriteName,
            float angle,
            float linearSpeed,
            float maxDistance,
            int damage
        );
        void Update(float dt);
        void Render();
        bool Is(std::string type);
        int GetDamage();
};

#endif