#ifndef BULLET_H
#define BULLET_H

#include "Component.h"

#define BULLET1_SPR     "assets/img/minionbullet1.png"
#define BULLET1_SPEED   600.0f
#define BULLET1_DAMAGE  10

class Bullet: public Component {
    private:
        Vec2 speed;
        float distanceLeft;
        int damage;

    public:
        Bullet(
            GameObject& associated,
            float angle,
            float speed,
            int damage,
            float maxDistance,
            std::string spriteName
        );
        void Update(float dt);
        void Render();
        bool Is(std::string type);
        int GetDamage();
};

#endif