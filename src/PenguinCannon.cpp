#include "GentooEngine.h"
#include "GameData.h"
#include "PenguinCannon.h"
#include "PenguinBody.h"
#include "Bullet.h"

PenguinCannon::PenguinCannon (
    GameObject& associated, GameObject& penguinBody
): Component(associated) {
    
    sprite = new Sprite(associated);
    associated.AddComponent(sprite);

    Collider* collider = new Collider(associated);
    associated.AddComponent(collider);

    // sylar's extra sfx
    shotSound = new Sound(associated, PENGUINC_SHOT_SOUND);
    associated.AddComponent(shotSound);

    pbody = Game::GetInstance().GetCurrentState().GetObjectPtr(&penguinBody);
    angle = 0;

    cooldown = Timer(PENGUINC_SHOT_COOLDOWN, PENGUINC_SHOT_TIMESTART);
}

void PenguinCannon::Start () {
    sprite->Open(PENGUINC_SPRITE);
    associated.box.offset = Vec2(PENGUINC_CENTER_OFFSET);   // sylar's extra positioning
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
    Vec2 pbodyPosition = pbody.lock()->box.GetPosition();
    angle = pbodyPosition.AngleTo(target);
    associated.angleDeg = Rad2Deg(angle);
    associated.box.SetPosition(pbodyPosition);

    cooldown.Update(dt);
    if (cooldown.IsOver()) {
        if (input.MousePress(MOUSE_BUTTON_LEFT)) {
            Shoot(target);
            cooldown.Reset();
        }
        GameData::movementAllowed = true;
    } else {
        GameData::UpdateHudCd(dt);
    }
}

void PenguinCannon::Render () {}

void PenguinCannon::Shoot (Vec2 target) {
    GameObject* bullet = new GameObject(PENGUINC_BULLET_LAYER, PENGUINC_BULLET_LABEL);
    Vec2 cannonPosition = associated.box.GetPosition();
    Vec2 radius(PENGUINC_BULLET_OFFSET);

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
    bullet->box.RotateAround(cannonPosition, radius, angle);
    Game::GetInstance().GetCurrentState().AddObject(bullet);

    // sylar's extra sfx
    shotSound->Play();
}

void PenguinCannon::NotifyCollision (GameObject& other) {
    if (not pbody.expired())
        pbody.lock()->NotifyCollision(other);
}

float PenguinCannon::GetRelativeCooldown () {
    return ((1.0f/PENGUINC_SHOT_COOLDOWN) * cooldown.Get());
}

int PenguinCannon::GetHP () {
    if (pbody.expired()) return 0;
    return ((PenguinBody*)pbody.lock()->GetComponent("PenguinBody"))->GetHP();
}

bool PenguinCannon::Is (std::string type) {
    return (type == "PenguinCannon");
}