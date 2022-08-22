#ifndef PENGUIN_CANNON_H
#define PENGUIN_CANNON_H

#include "Component.h"
#include "Timer.h"

// sylar's extra positioning
#include "PenguinBody.h"

#define PENGUINC_SPRITE                 "assets/img/cubngun.png"
#define PENGUINC_SHOT_COOLDOWN          0.5f
#define PENGUINC_LAYER                  3

#define PENGUINC_BULLET_LABEL           "Projectile"
#define PENGUINC_BULLET_SPRITE          "assets/img/minionbullet2.png"
#define PENGUINC_BULLET_FRAME_COUNT     3
#define PENGUINC_BULLET_FRAME_TIME      0.04f
#define PENGUINC_BULLET_FRAME_ONESHOT   false
#define PENGUINC_BULLET_ARC_DISTANCE    50.0f, 0.0f
#define PENGUINC_BULLET_SPEED           600.0f
#define PENGUINC_BULLET_DAMAGE          10
#define PENGUINC_BULLET_LAYER           2

// sylar's extra positioning
#define PENGUINC_ARC_DISTANCE           5.75f, 0.0f

class PenguinCannon: public Component {
    private:
        std::weak_ptr<GameObject> pbody;
        float angle;
        Timer cooldown;

        // sylar's extra positioning
        PenguinBody* pbodyCp;
        Vec2 arcPlacement;
    
    public:
        PenguinCannon(GameObject& associated, GameObject& penguinBody);
        void Update(float dt);
        void Render();
        void Shoot(Vec2 target);
        void NotifyCollision(GameObject& other);
        bool Is(std::string type);
};

#endif