#include "PenguinCannon.h"
#include "Game.h"
#include "Camera.h"
#include "InputManager.h"
#include "Sprite.h"
#include "Collider.h"
#include "Bullet.h"

PenguinCannon::PenguinCannon (
    GameObject& associated, GameObject& penguinBody
): Component(associated) {
    
    Sprite* sprite = new Sprite(associated, PENGUINC_SPRITE);
    associated.AddComponent(sprite);
    Collider* collider = new Collider(associated);
    associated.AddComponent(collider);
    associated.label = "Player";

    pbody = Game::GetInstance().GetState().GetObjectPtr(&penguinBody);
    angle = 0;

    // sylar's extra positioning
    pbodyCp = (PenguinBody*)pbody.lock()->GetComponent("PenguinBody");
    arcPlacement = Vec2(PENGUINC_ARC_DISTANCE) * (PI*2);
}

void PenguinCannon::Update (float dt) {
    InputManager& input = InputManager::GetInstance();
    Vec2 target = input.GetMousePosition();

    if (pbody.expired()) {
        associated.RequestDelete();
        return;
    }

    // // idj's original positioning
    // Vec2 pbodyPosition = pbody.lock()->box.GetCenter();
    // angle = associated.box.GetCenter().AngleTo(target);
    // associated.angleDeg = Rad2Deg(angle);
    // associated.box.SetPosition(pbodyPosition);

    // sylar's extra positioning
    Vec2 pbodyPosition = pbodyCp->GetPosition();
    angle = pbodyPosition.AngleTo(target);
    Vec2 position = pbodyPosition + arcPlacement.Rotate(-angle);
    associated.angleDeg = Rad2Deg(angle);
    associated.box.SetPosition(position);

    if (input.MousePress(MOUSE_BUTTON_LEFT)) {
        Shoot(target);
    }
}

void PenguinCannon::Render () {}

void PenguinCannon::Shoot (Vec2 target) {
    GameObject* bullet = new GameObject();
    Vec2 cannonPosition = associated.box.GetCenter();
    Vec2 bulletArcPlacement(PENGUINC_BULLET_ARC_DISTANCE);
    Vec2 bulletPosition = cannonPosition + bulletArcPlacement.Rotate(-angle);
    float targetDistance = bulletPosition.DistanceTo(target);

    bullet->AddComponent(
        new Bullet(
            *bullet, PENGUINC_BULLET_SPRITE,
            angle, PENGUINC_BULLET_SPEED, targetDistance,
            PENGUINC_BULLET_DAMAGE,
            PENGUINC_BULLET_FRAME_COUNT, PENGUINC_BULLET_FRAME_TIME
        )
    );
    bullet->box.SetPosition(bulletPosition);
    Game::GetInstance().GetState().AddObject(bullet);
}

void PenguinCannon::NotifyCollision (GameObject& other) {
    if (other.label == "Projectile") {
        pbodyCp->NotifyCollision(other);
    }
}

bool PenguinCannon::Is (std::string type) {
    return (type == "PenguinCannon");
}