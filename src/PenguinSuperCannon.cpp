#include "GentooEngine.h"
#include "PenguinSuperCannon.h"
#include "Bullet.h"

PenguinSuperCannon::PenguinSuperCannon (
    GameObject& associated, GameObject& penguinBody
): PenguinCannon(associated, penguinBody) {}

void PenguinSuperCannon::Start () {
    sprite->Open(PENGUINSC_SPRITE);
    associated.box.offset = Vec2(PENGUINC_CENTER_OFFSET);
}

void PenguinSuperCannon::Shoot (Vec2 target) {
    GameObject* bullet = new GameObject(PENGUINC_BULLET_LAYER, PENGUINSC_BULLET_LABEL);
    Vec2 cannonPosition = associated.box.GetPosition();
    Vec2 radius(PENGUINC_BULLET_OFFSET);

    bullet->AddComponent(
        new Bullet(
            *bullet, PENGUINSC_BULLET_SPRITE,
            angle, PENGUINC_BULLET_SPEED, PENGUINC_BULLET_RANGE,
            PENGUINC_BULLET_DAMAGE,
            PENGUINC_BULLET_FRAME_COUNT, PENGUINC_BULLET_FRAME_TIME, PENGUINC_BULLET_FRAME_ONESHOT,
            PENGUINSC_BULLET_TARGETS,
            PENGUINC_BULLET_SOUND_SHOT, PENGUINC_BULLET_SOUND_HIT
        )
    );
    bullet->box.RotateAround(cannonPosition, radius, angle);
    Game::GetInstance().GetCurrentState().AddObject(bullet);

    // sylar's extra sfx
    shotSound->Play();
}