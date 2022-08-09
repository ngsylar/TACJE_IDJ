#ifndef BULLET_H
#define BULLET_H

#include "Component.h"

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
            int damage,
            int spriteFrameCount=1,
            float spriteFrameTime=1.0f
        );
        void Update(float dt);
        void Render();
        bool Is(std::string type);
        int GetDamage();
};

#endif