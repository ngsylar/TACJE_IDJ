#include "GentooEngine.h"
#include "PenguinCannon.h"
#include "Bullet.h"

PenguinCannon::PenguinCannon (
    GameObject& associated, GameObject& penguinBody
): Component(associated) {
    
    Sprite* sprite = new Sprite(associated, PENGUINC_SPRITE);
    associated.AddComponent(sprite);
    Collider* collider = new Collider(associated);
    associated.AddComponent(collider);

    // sylar's extra sfx
    shotSound = new Sound(associated, PENGUINC_SHOT_SOUND);
    associated.AddComponent(shotSound);

    pbody = Game::GetInstance().GetCurrentState().GetObjectPtr(&penguinBody);
    angle = 0;

    // sylar's extra positioning
    pbodyCp = (PenguinBody*)pbody.lock()->GetComponent("PenguinBody");
    arcPlacement = Vec2(PENGUINC_ARC_DISTANCE) * (PI*2);

    cooldown = Timer(PENGUINC_SHOT_COOLDOWN, PENGUINC_SHOT_COOLDOWN);
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
    Vec2 position = pbodyPosition + arcPlacement.Rotate(angle);
    associated.angleDeg = Rad2Deg(angle);
    associated.box.SetPosition(position);

    cooldown.Update(dt);
    if (cooldown.IsOver() and input.MousePress(MOUSE_BUTTON_LEFT)) {
        Shoot(target);
        cooldown.Reset();
    }
}

void PenguinCannon::Render () {}

int PenguinCannon::GetHP () {
    return pbodyCp->GetHP();
}

void PenguinCannon::Shoot (Vec2 target) {
    GameObject* bullet = new GameObject(PENGUINC_BULLET_LAYER, PENGUINC_BULLET_LABEL);
    Vec2 cannonPosition = associated.box.GetCenter();
    Vec2 bulletArcPlacement(PENGUINC_BULLET_ARC_DISTANCE);
    Vec2 bulletPosition = cannonPosition + bulletArcPlacement.Rotate(angle);

    bullet->AddComponent(
        new Bullet(
            *bullet, PENGUINC_BULLET_SPRITE,
            angle, PENGUINC_BULLET_SPEED, PENGUINC_BULLET_RANGE,
            PENGUINC_BULLET_DAMAGE,
            PENGUINC_BULLET_FRAME_COUNT, PENGUINC_BULLET_FRAME_TIME, PENGUINC_BULLET_FRAME_ONESHOT,
            PENGUINC_BULLET_TARGETS,
            PENGUINC_BULLET_SOUND_SHOT, PENGUINC_BULLET_SOUND_HIT
        )
    );
    bullet->box.SetPosition(bulletPosition);
    Game::GetInstance().GetCurrentState().AddObject(bullet);

    // sylar's extra sfx
    shotSound->Play();
}

void PenguinCannon::NotifyCollision (GameObject& other) {
    pbodyCp->NotifyCollision(other);
}

bool PenguinCannon::Is (std::string type) {
    return (type == "PenguinCannon");
}