#ifndef BULLET_H
#define BULLET_H

#include "Component.h"

class Bullet: public Component {
    private:
        Vec2 speed;
        float distanceLeft;
        int damage;
        bool targetsPlayer;

    public:
        Bullet(
            GameObject& associated,
            std::string spriteName,
            float angle,
            float linearSpeed,
            float maxDistance,
            int damage,
            int spriteFrameCount=1,
            float spriteFrameTime=0.0f,
            bool spriteFramesOneshot=false,
            bool targetsPlayer=false
        );
        void Update(float dt);
        void Render();
        int GetDamage();
        void NotifyCollision(GameObject& other);
        bool IsTargetingPlayer();
        bool IsTargetingEnemy();
        bool Is(std::string type);
};

#endif