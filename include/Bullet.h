#ifndef BULLET_H
#define BULLET_H

#include "Component.h"

#define BULLET1_SPRITE  "assets/img/minionbullet1.png"
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
            std::string spriteName,
            float angle,
            float speed,
            float maxDistance,
            int damage
        );
        void Update(float dt);
        void Render();
        bool Is(std::string type);
        int GetDamage();
};

#endif