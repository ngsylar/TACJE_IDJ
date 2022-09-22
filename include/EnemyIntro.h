#ifndef ENEMY_INTRO_H
#define ENEMY_INTRO_H

#include "AlienBoss.h"
#include "MinionBoss.h"

class AlienIntro: public Component {
    private:
        bool boss;
        Sprite* sprite;
        float scale;
        int minionCount, minionsReady;
        std::vector<std::weak_ptr<GameObject>> minionArray;
        Timer countdown;

    public:
        AlienIntro(
            GameObject& associated,
            int minionCount,
            bool boss=false
        );
        void Start();
        void Update(float dt);
        void IncreaseReadyMinions();
        void GenerateNPC();
        bool Is(std::string type);
};

class MinionIntro: public Component {
    private:
        std::weak_ptr<GameObject> alienCenter;
        bool boss;
        int index;
        Sprite* sprite;
        float scale, desiredScale;
        float arc;
        Vec2 alienPosition, position;
        Timer countdown;
        bool ready, readyPosition, readyScale;

    public:
        MinionIntro(
            GameObject& associated,
            GameObject& alienCenter,
            int index,
            float arcOffsetDeg=0.0f,
            bool boss=false
        );
        void Start();
        void Update(float dt);
        float GetScale();
        bool Is(std::string type);
};

#endif