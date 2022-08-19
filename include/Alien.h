#ifndef ALIEN_H
#define ALIEN_H

#include <queue>

#include "InputManager.h"
#include "Component.h"

// sylar's extra positioning
#include "Sprite.h"

#define ALIEN_SPRITE            "assets/img/alien.png"
#define ALIEN_START_POSITION    512, 300
#define ALIEN_START_HP          100
#define ALIEN_LINEAR_SPEED      200.0f
#define ALIEN_PASSING_DISTANCE  10.0f
#define ALIEN_ROTATION_SPEED    20.0f
#define ALIEN_MINIONS_AMOUNT    6

class Alien: public Component {
    private:
        class Action {
            public:
                enum ActionType {MOVE, SHOOT};
                ActionType type;
                Vec2 pos;

                Action(ActionType type, Vec2 pos);
        };
        
        int hp;
        int nMinions;
        Vec2 speed;
        std::queue<Action> taskQueue;
        std::vector<std::weak_ptr<GameObject>> minionArray;
        
        Action ScheduleAction(InputManager* input, Action::ActionType type);

        // sylar's alien breath extra effects
        Sprite* sprite;
        bool breathIn;
        void BreathAnimation(float dt);

    public:
        Alien(GameObject& associated, int nMinions);
        ~Alien();
        void Start();
        void Update(float dt);
        void Render();
        void NotifyCollision(GameObject& other);
        bool Is(std::string type);
};

#endif