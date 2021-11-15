#include <cmath>

#include "Alien.h"
#include "Game.h"
#include "InputManager.h"
#include "Camera.h"
#include "Sprite.h"
#include "Minion.h"
// #include "Sound.h"

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
    GameObject* minion;

    for (int i=0; i < nMinions; i++) {
        minion = new GameObject();
        minion->AddComponent(new Minion(*minion, associated, (float)i*((PI*2)/nMinions)));
        minionArray.push_back(Game::GetInstance().GetState().AddObject(minion));
    }
}

// Face::Face (GameObject& associated): Component(associated) {
//     hitpoints = FCE_INIT_HP;
// }

// Face::~Face () {}

// void Face::Damage (int damage) {
//     Sound* sound;

//     hitpoints -= damage;
//     if (hitpoints <= 0) {
//         associated.RequestDelete();
//         sound = (Sound*)associated.GetComponent("Sound");
//         if (sound) {
//             sound->Play();
//         }
//     }
// }

// void Face::Update (float dt) {
//     InputManager& input = InputManager::GetInstance();

//     if ((input.MousePress(MOUSE_BUTTON_LEFT) or
//         input.MousePress(MOUSE_BUTTON_RIGHT)) and
//         associated.box.Contains(
//             input.GetMouseX()+Camera::pos.x,
//             input.GetMouseY()+Camera::pos.y)
//     ) {
//         Damage(std::rand() % 10 + 10);
//     }
// }

void Alien::Update (float dt) {
    InputManager& input = InputManager::GetInstance();

    if (input.MousePress(MOUSE_BUTTON_LEFT)) {
        taskQueue.push(Action(
            Action::SHOOT,
            input.GetMouseX()+Camera::pos.x,
            input.GetMouseY()+Camera::pos.y
        ));
    }
    if (input.MousePress(MOUSE_BUTTON_RIGHT)) {
        taskQueue.push(Action(
            Action::MOVE,
            input.GetMouseX()+Camera::pos.x,
            input.GetMouseY()+Camera::pos.y
        ));
    }

    // apagar isso dps
    if (input.KeyPress(KEY_SPACE)) {
        taskQueue.pop();
    }

    if (!taskQueue.empty()) {
        Action action = taskQueue.front();
        Vec2 alienPos;
        float dX=0, dY=0;

        switch (action.type) {
            case Action::SHOOT:
                break;

            case Action::MOVE:
                alienPos = associated.box.GetCenter();

                dX = action.pos.x-alienPos.x;
                dY = action.pos.y-alienPos.y;
                speed = Vec2(dX, dY);
                speed.Normalize();
                speed *= 200.0f * dt;
                associated.box.x += speed.x;
                associated.box.y += speed.y;

                if ((abs(action.pos.x-alienPos.x) <= 10.0f) && (abs(action.pos.y-alienPos.y) <= 10.0f)) {
                    speed = Vec2();
                    taskQueue.pop();
                }
                break;
            
            default: break;
        }
    }
}

void Alien::Render () {}

bool Alien::Is (std::string type) {
    return (type == "Alien");
}