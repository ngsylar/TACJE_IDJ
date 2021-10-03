#include "Face.h"
#include "InputManager.h"
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

    if ((input.MousePress(LEFT_MOUSE_BUTTON) or input.MousePress(RIGHT_MOUSE_BUTTON)) and associated.box.Contains(input.GetMouseX(),input.GetMouseY())) {
        Damage(std::rand() % 10 + 10);
    }
}

void Face::Render () {}

bool Face::Is (std::string type) {
    return (type == "Face");
}