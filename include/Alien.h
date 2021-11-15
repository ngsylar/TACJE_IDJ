#ifndef ALIEN_H
#define ALIEN_H

#include <queue>

#include "Component.h"

#define ALIEN_INITIAL_HP 100

class Alien: public Component {
    private:
        class Action {
            public:
                enum ActionType {MOVE, SHOOT};
                ActionType type;
                Vec2 pos;

                Action(ActionType type, float x, float y);
        };

        Vec2 speed;
        int hp;
        int nMinions;
        std::queue<Action> taskQueue;
        std::vector<std::weak_ptr<GameObject>> minionArray;
        
    public:
        Alien(GameObject& associated, int nMinions);
        ~Alien();
        void Start();
        void Update(float dt);
        void Render();
        bool Is(std::string type);
};

#endif