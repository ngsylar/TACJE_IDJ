#include "Face.h"
#include "Sound.h"

#define INITIAL_HP 30
#define NO_HP(hp) (hp <= 0)
#define REPEAT_OFF 1

Face::Face (GameObject& associated): Component(associated) {
    hitpoints = INITIAL_HP;
}

void Face::Damage (int damage) {
    Sound* sound;

    hitpoints -= damage;
    if (NO_HP(hitpoints)) {
        associated.RequestDelete();
        sound = (Sound*)associated.GetComponent("Sound");
        if (sound) {
            sound->Play(REPEAT_OFF);
        }
    }
}

void Face::Update (float dt) {}

void Face::Render () {}

bool Face::Is (std::string type) {
    return (type == "Face");
}