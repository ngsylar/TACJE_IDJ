#ifndef MINION_BOSS_H
#define MINION_BOSS_H

#include "Minion.h"

#define MINION_BOSS_SPRITE          "assets/img/minion2.png"
#define MINION_BOSS_HP_MODIFIER     100
#define MINION_BOSS_BULLET_LABEL    "MinionBullet"
#define MINION_BOSS_BULLET_SPRITE   "assets/img/minionbullet3.png"
#define MINION_BOSS_BULLET_OFFSET   25.0f, 0.0f
#define MINION_BOSS_BULLET_TARGETS  {"Player", "PenguinBullet"}
#define MINION_BOSS_BULLET_SPEED    {75.0f, 600.0f, 150.0f, 0.0f}
#define MINION_BOSS_DEATH_SPRITE    "assets/img/minion2death.png"

class MinionBoss: public Minion {
    private:
        friend class AlienBoss;
        bool still;

    public:
        MinionBoss(
            GameObject& associated,
            GameObject& alienCenter,
            float arcOffsetDeg=0.0f
        );
        void Start();
        void Update(float dt);
        void Shoot(
            Vec2 target,
            float bulletSpeed,
            std::string bulletSoundShot=""
        );
        void ExplodeAnimation();
};

#endif