#ifndef PENGUIN_SUPER_CANNON_H
#define PENGUIN_SUPER_CANNON_H

#include "PenguinCannon.h"

#define PENGUINSC_SPRITE            "assets/img/cubngun2.png"
#define PENGUINSC_BULLET_LABEL      "PenguinBullet"
#define PENGUINSC_BULLET_SPRITE     "assets/img/penguinbullet2.png"
#define PENGUINSC_BULLET_TARGETS    {"Enemy", "MinionBullet"}

class PenguinSuperCannon: public PenguinCannon {
    public:
        PenguinSuperCannon(GameObject& associated, GameObject& penguinBody);
        void Start();
        void Shoot(Vec2 target);
};

#endif