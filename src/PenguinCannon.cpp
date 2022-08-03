#include "PenguinCannon.h"
#include "Game.h"
#include "Camera.h"
#include "InputManager.h"
#include "Sprite.h"
#include "Bullet.h"

PenguinCannon::PenguinCannon (
    GameObject& associated, GameObject& penguinBody
): Component(associated) {
    Sprite* sprite = new Sprite(associated, PENGUINC_SPRITE);
    associated.AddComponent(sprite);
    pbody = Game::GetInstance().GetState().GetObjectPtr(&penguinBody);
    angle = 0;
}

void PenguinCannon::Update (float dt) {
    InputManager& input = InputManager::GetInstance();
    Vec2 target = input.GetMousePosition();

    if (pbody.expired()) {
        associated.RequestDelete();
        return;
    }

    associated.box.SetPosition(pbody.lock()->box.GetCenter());
    angle = associated.box.GetCenter().AngleTo(target);
    associated.angleDeg = Rad2Deg(angle);

    if (input.MousePress(MOUSE_BUTTON_LEFT)) {
        Shoot(target);
    }
}

void PenguinCannon::Render () {}

void PenguinCannon::Shoot (Vec2 target) {
    Vec2 cannonPosition = associated.box.GetCenter();
    float distance = cannonPosition.DistanceTo(target);

    GameObject* bullet = new GameObject();
    bullet->AddComponent(
        new Bullet(
            *bullet, MINION_BULLET_SPRITE,
            angle, MINION_BULLET_SPEED, distance,
            MINION_BULLET_DAMAGE
        )
    );
    bullet->box.SetPosition(cannonPosition);
    Game::GetInstance().GetState().AddObject(bullet);
}

bool PenguinCannon::Is (std::string type) {
    return (type == "PenguinCannon");
}