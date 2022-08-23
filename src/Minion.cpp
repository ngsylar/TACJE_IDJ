#include "Minion.h"
#include "Game.h"
#include "Collider.h"
#include "Sprite.h"
#include "Sound.h"
#include "Bullet.h"

Minion::Minion (
    GameObject& associated,
    GameObject& alienCenter,
    float arcOffsetDeg
): Component(associated) {

    Sprite* sprite = new Sprite(associated, MINION_SPRITE);
    int rangeStart = MINION_SCALE_MIN * 100;
    int scaleMod = ((MINION_SCALE_MAX - MINION_SCALE_MIN) * 100) + 1;
    sprite->SetScale((float)((rand() % scaleMod) + rangeStart) / 100.0f);
    associated.AddComponent(sprite);

    Collider* collider = new Collider(associated);
    associated.AddComponent(collider);

    this->alienCenter = Game::GetInstance().GetState().GetObjectPtr(&alienCenter);
    arc = arcOffsetDeg;
    hp = sprite->GetScale().x * MINION_HP_MODIFIER;
}

void Minion::Update (float dt) {
    if (hp <= 0) {
        return;
    }
    if (alienCenter.expired()) {
        associated.RequestDelete();
        return;
    }
    
    arc += PI * MINION_ARC_SPEED * dt;
    Vec2 alienPosition = alienCenter.lock()->box.GetCenter();
    float alienScale = ((Sprite*)alienCenter.lock()->GetComponent("Sprite"))->GetScale().x;
    Vec2 minionDistance = Vec2(MINION_ARC_DISTANCE) * alienScale;
    Vec2 minionPlacement = alienPosition + minionDistance.Rotate(-arc);
    associated.box.SetPosition(minionPlacement);

    Vec2 minionPosition = associated.box.GetCenter();
    associated.angleDeg = minionPosition.AngleDegTo(alienPosition) + MINION_ANGLEDEG_ADJUST;
}

void Minion::Render () {}

void Minion::Shoot (Vec2 target) {
    Vec2 minionPosition = associated.box.GetCenter();
    float angle = minionPosition.AngleTo(target);
    float distance = minionPosition.DistanceTo(target);

    GameObject* bullet = new GameObject(MINION_BULLET_LAYER, MINION_BULLET_LABEL);
    bullet->AddComponent(
        new Bullet(
            *bullet, MINION_BULLET_SPRITE,
            angle, MINION_BULLET_SPEED, distance,
            MINION_BULLET_DAMAGE,
            MINION_BULLET_FRAME_COUNT, MINION_BULLET_FRAME_TIME, MINION_BULLET_FRAME_ONESHOT,
            MINION_BULLET_TARGETS
        )
    );
    bullet->box.SetPosition(minionPosition);
    Game::GetInstance().GetState().AddObject(bullet);
}

void Minion::ExplodeAnimation () {
    State& state = Game::GetInstance().GetState();

    GameObject* explosion = new GameObject(MINION_DEATH_LAYER, MINION_DEATH_LABEL);
    explosion->AddComponent(
        new Sprite(
            *explosion, MINION_DEATH_SPRITE,
            MINION_DEATH_FRAME_COUNT, MINION_DEATH_FRAME_TIME,
            MINION_DEATH_FRAME_ONESHOT, MINION_DEATH_SELFDESTRUCTION
        )
    );
    explosion->box.SetPosition(associated.box.GetCenter());
    state.AddObject(explosion);
    
    GameObject* boom = new GameObject();
    Sound* explosionSound = new Sound(*boom, MINION_DEATH_SOUND);
    boom->AddComponent(explosionSound);
    state.AddObject(boom);
    explosionSound->Play(MINION_DEATH_SOUND_TIMES, MINION_DEATH_SELFDESTRUCTION);
}

Vec2 Minion::GetPosition () {
    return associated.box.GetCenter();
}

void Minion::NotifyCollision (GameObject& other) {
    Bullet* bullet = (Bullet*)other.GetComponent("Bullet");
    if ((bullet != nullptr) and bullet->IsAimingAt(MINION_LABEL)) {
        hp -= bullet->GetDamage();
    }
}

bool Minion::IsDead () {
    return (hp <= 0);
}

bool Minion::Is (std::string type) {
    return (type == "Minion");
}