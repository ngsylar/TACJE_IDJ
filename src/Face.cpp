#include "Face.h"
#include "InputManager.h"
#include "Camera.h"
#include "Sound.h"

Face::Face (GameObject& associated): Component(associated) {
    hitpoints = FCE_INIT_HP;
}

Face::~Face () {}

void Face::Damage (int damage) {
    Sound* sound;

    hitpoints -= damage;
    if (hitpoints <= 0) {
        associated.RequestDelete();
        sound = (Sound*)associated.GetComponent("Sound");
        if (sound) {
            sound->Play();
        }
    }
}

void Face::Update (float dt) {
    InputManager& input = InputManager::GetInstance();

    if ((input.MousePress(MOUSE_BUTTON_LEFT) or
        input.MousePress(MOUSE_BUTTON_RIGHT)) and
        associated.box.Contains(
            input.GetMouseX()+Camera::pos.x,
            input.GetMouseY()+Camera::pos.y)
    ) {
        Damage(std::rand() % 10 + 10);
    }
}

void Face::Render () {}

bool Face::Is (std::string type) {
    return (type == "Face");
}