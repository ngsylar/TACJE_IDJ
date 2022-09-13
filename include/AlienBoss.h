#ifndef ALIEN_BOSS_H
#define ALIEN_BOSS_H

#include "Alien.h"

#define ALIEN_BOSS_LABEL                    "Enemy"
#define ALIEN_BOSS_SPRITE                   "assets/img/boss.png"
#define ALIEN_BOSS_START_HP                 400
#define ALIEN_BOSS_MINION_COUNT             {6, 5}
#define ALIEN_BOSS_SHOT_COOLDOWN            {0.5f, 0.1f, 0.25f, 0.0f}
#define ALIEN_BOSS_SHOT_SPIRAL_COUNT        3

#define ALIEN_BOSS_DEATH_LABEL              "Explosion"
#define ALIEN_BOSS_DEATH_SOUND              "assets/audio/boomAlien.wav"
#define ALIEN_BOSS_DEATH_SOUND_TIMES        1
#define ALIEN_BOSS_DEATH_SPRITE             "assets/img/bossdeath.png"
#define ALIEN_BOSS_DEATH_FRAME_COUNT        4
#define ALIEN_BOSS_DEATH_FRAME_TIME         0.06f
#define ALIEN_BOSS_DEATH_FRAME_ONESHOT      true
#define ALIEN_BOSS_DEATH_SELFDESTRUCTION    true
#define ALIEN_BOSS_DEATH_LAYER              7

class AlienBoss: public Alien {
    private:
        enum ShotStyle {SINGLE, MULTIPLE, SPIRAL, SQUAD};

        std::vector<float> shotStylesCooldown;
        ShotStyle shotStyle;
        static int shotSpiralId;

        void ActionRest(float dt);
        void ActionShoot(float dt);
        void ActionMove(float dt);
    
    public:
        AlienBoss(GameObject& associated, int minionCount);
        void Update(float dt);
};

#endif