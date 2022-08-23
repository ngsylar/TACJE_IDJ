#ifndef BULLET_H
#define BULLET_H

#include "Component.h"

#define BULLET_HIT_SOUND_TIMES      1
#define BULLET_HIT_SELFDESTRUCTION  true

class Bullet: public Component {
    private:
        Vec2 speed;
        float distanceLeft;
        int damage;
        std::vector<std::string> targets;
        std::string hitSoundFilename;       // sylar's extra sfx

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
            std::vector<std::string> targetLabels={},
            std::string hitSoundFilename=""
        );
        void Update(float dt);
        void Render();
        bool IsAimingAt(std::string targetLabel);
        int GetDamage();
        void PlayHitSound();
        void NotifyCollision(GameObject& other);
        bool Is(std::string type);
};

#endif