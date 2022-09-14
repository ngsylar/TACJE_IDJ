#ifndef ENEMY_INTRO_H
#define ENEMY_INTRO_H

#include "AlienBoss.h"
#include "MinionBoss.h"

class AlienIntro: public Component {
    private:
        bool boss;
        Sprite* sprite;
        float scale;
        int minionCount;
        std::vector<std::weak_ptr<GameObject>> minionArray;

    public:
        AlienIntro(
            GameObject& associated,
            int minionCount,
            bool boss=false
        );
        void Start();
        void Update(float dt);
        void Render();
        bool Is(std::string type);
};

class MinionIntro: public Component {
    private:
        std::weak_ptr<GameObject> alienCenter;
        bool boss;
        Sprite* sprite;
        float scale, desiredScale;
        float arc;
        Vec2 alienPosition, position;
        Timer generator;

    public:
        MinionIntro(
            GameObject& associated,
            GameObject& alienCenter,
            float arcOffsetDeg=0.0f,
            bool boss=false
        );
        void Start();
        void Update(float dt);
        void Render();
        bool Is(std::string type);
};

#endif