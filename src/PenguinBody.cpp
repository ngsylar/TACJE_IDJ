#include "PenguinBody.h"
#include "Game.h"
#include "Camera.h"
#include "InputManager.h"
#include "Sprite.h"
#include "PenguinCannon.h"

PenguinBody* PenguinBody::player;

PenguinBody::PenguinBody (GameObject& associated): Component(associated) {
    Sprite* sprite = new Sprite(associated, PENGUINB_SPRITE);
    associated.AddComponent(sprite);
    player = this;

    hp = PENGUINB_START_HP;
    linearSpeed = 0.0f;
    angle = 0.0f;
}

PenguinBody::~PenguinBody () {
    Camera::Unfollow();
    player = nullptr;
}

void PenguinBody::Start () {
    GameObject* pcannonObj = new GameObject();
    pcannonObj->AddComponent(new PenguinCannon(*pcannonObj, associated));
    pcannon = Game::GetInstance().GetState().AddObject(pcannonObj);
    rotationRadSpeed = Deg2Rad(PENGUINB_ROTATION_SPEED);
}

void PenguinBody::Update (float dt) {
    InputManager& input = InputManager::GetInstance();

    if (hp <= 0) {
        associated.RequestDelete();
        pcannon.lock()->RequestDelete();
        return;
    }

    if (input.IsKeyDown(KEY_W)) {
        if (linearSpeed < PENGUINB_MAX_SPEED) {
            linearSpeed += PENGUINB_ACCELERATION * dt;
        } else linearSpeed = PENGUINB_MAX_SPEED;
    }
    if (input.IsKeyDown(KEY_S)) {
        if (linearSpeed > (-PENGUINB_MAX_SPEED*0.5f)) {
            linearSpeed -= (PENGUINB_ACCELERATION*0.5) * dt;
        } else linearSpeed = (-PENGUINB_MAX_SPEED*0.5f);
    }
    if (input.IsKeyDown(KEY_A)) {
        angle -= rotationRadSpeed * dt;
        associated.angleDeg = Rad2Deg(angle);
    }
    if (input.IsKeyDown(KEY_D)) {
        angle += rotationRadSpeed * dt;
        associated.angleDeg = Rad2Deg(angle);
    }
    
    speed = Vec2().DirectionFrom(angle) * linearSpeed;
    associated.box.Translate(speed * dt);
}

void PenguinBody::Render () {}

bool PenguinBody::Is (std::string type) {
    return (type == "PenguinBody");
}