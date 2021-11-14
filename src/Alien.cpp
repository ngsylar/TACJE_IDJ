#include <cmath>

#include "Alien.h"
#include "InputManager.h"
#include "Camera.h"
#include "Sprite.h"
// #include "Sound.h"

Alien::Alien (GameObject& associated, int nMinions): Component(associated) {
    Sprite* sprite = new Sprite(associated, ALIEN_SPR);
    associated.AddComponent(sprite);
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
    // editar
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
        float dX=0, dY=0;
        std::string coiso;

        switch (action.type) {
            case Action::SHOOT:
                break;

            case Action::MOVE:
                dX = action.pos.x-associated.box.x;
                dY = action.pos.y-associated.box.y;
                speed = Vec2(dX, dY);
                speed.Normalize();
                speed *= 200.0f * dt;
                associated.box.x += speed.x;
                associated.box.y += speed.y;

                // apagar isso dps
                coiso = std::to_string(associated.box.x)+" "+std::to_string(associated.box.y);
                SDL_Log(coiso.c_str());

                if ((abs(action.pos.x-associated.box.x) <= 10.0f) && (abs(action.pos.y-associated.box.y) <= 10.0f)) {
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