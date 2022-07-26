#include "Alien.h"
#include "Camera.h"
#include "Resources.h"
#include "Sprite.h"

Alien::Alien (GameObject& associated, int nMinions): Component(associated) {
    Sprite* sprite = new Sprite(associated, ALIEN_SPR);
    associated.AddComponent(sprite);
    this->nMinions = nMinions;
    hp = ALIEN_INITIAL_HP;
}

Alien::Action::Action (ActionType type, float x, float y) {
    this->type = type;
    pos = Vec2(x, y);
}

Alien::~Alien () {
    minionArray.clear();
}

void Alien::Start () {
    // GameObject* minion;

    // for (int i=0; i < nMinions; i++) {
    //     minion = new GameObject();
    // }
}

Alien::Action Alien::ScheduleAction(InputManager* input, Action::ActionType type) {
    Action action(
        type,
        input->GetMouseX()+Camera::pos.x,
        input->GetMouseY()+Camera::pos.y
    );
    return action;
}

void Alien::Update (float dt) {
    InputManager& input = InputManager::GetInstance();
    
    if (hp <= 0) {
        associated.RequestDelete();
        return;
    }
    if (input.MousePress(MOUSE_BUTTON_RIGHT)) {
        taskQueue.push(ScheduleAction(&input, Action::MOVE));
    }
    if (input.MousePress(MOUSE_BUTTON_LEFT)) {
        taskQueue.push(ScheduleAction(&input, Action::SHOOT));
    }

    if (!taskQueue.empty()) {
        Action action = taskQueue.front();
        Vec2 alienPosition;
        float targetAngle;

        switch (action.type) {
            case Action::MOVE:
                alienPosition = associated.box.GetCenter();

                if (alienPosition.DistanceTo(action.pos) > ALIEN_MINIMUM_DISTANCE) {
                    targetAngle = alienPosition.AngleTo(action.pos);
                    speed = alienPosition.DirectionFrom(targetAngle);
                    associated.box.Translate(speed * ALIEN_SCALAR_SPEED * dt);
                } else {
                    associated.box.SetPosition(action.pos.x, action.pos.y);
                    taskQueue.pop();
                    speed = Vec2();
                }
                break;
            
            case Action::SHOOT:
                if (!minionArray.empty()) {
                    // Minion* minion = (Minion*)minionArray[rand()%nMinions].lock()->GetComponent("Minion");

                    // minion->Shoot(action.pos);
                }
                taskQueue.pop();
                break;
            
            default: break;
        }
    }
}

void Alien::Render () {}

bool Alien::Is (std::string type) {
    return (type == "Alien");
}