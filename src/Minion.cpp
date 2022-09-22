#include "GentooEngine.h"
#include "Minion.h"
#include "Alien.h"
#include "Bullet.h"
#include "PenguinBody.h"
#include "PenguinCannon.h"

Minion::Minion (
    GameObject& associated, GameObject& alienCenter, float arcOffsetDeg, float scale
): Component(associated) {

    sprite = new Sprite(associated);
    associated.AddComponent(sprite);

    Collider* collider = new Collider(associated);
    associated.AddComponent(collider);

    this->alienCenter = Game::GetInstance().GetCurrentState().GetObjectPtr(&alienCenter);
    this->scale = scale;
    arc = arcOffsetDeg;

    playDeathSound = true;
}

void Minion::Start () {
    sprite->Open(MINION_SPRITE);
    // int rangeStart = MINION_SCALE_MIN * 100;
    // int scaleMod = ((MINION_SCALE_MAX - MINION_SCALE_MIN) * 100) + 1;
    // sprite->SetScale((float)((rand() % scaleMod) + rangeStart) / 100.0f);
    sprite->SetScale(scale);

    hp = sprite->GetScale().x * MINION_HP_MODIFIER;
    damageTaken = 0;

    Vec2 alienPosition = alienCenter.lock()->box.GetPosition();
    float alienScale = ((Alien*)alienCenter.lock()->GetComponent("Alien"))->GetScale().x;
    Vec2 arcRadius = Vec2(MINION_ARC_RADIUS) * alienScale;
    Vec2 minionPosition = alienPosition + arcRadius.Rotate(-arc);
    associated.box.SetPosition(minionPosition);
}

void Minion::Update (float dt) {
    if (alienCenter.expired()) {
        playDeathSound = false;
        ExplodeAnimation();
        associated.RequestDelete();
        return;
    }
    if (damageTaken > 0) {
        hp -= damageTaken;
        damageTaken = 0;
    }
    if (hp <= 0) {
        return;
    }
    
    arc += PI * MINION_ARC_SPEED * dt;
    Vec2 alienPosition = alienCenter.lock()->box.GetPosition();
    float alienScale = ((Alien*)alienCenter.lock()->GetComponent("Alien"))->GetScale().x;
    Vec2 arcRadius = Vec2(MINION_ARC_RADIUS) * alienScale;
    associated.box.RotateAround(alienPosition, arcRadius, -arc);

    Vec2 minionPosition = associated.box.GetPosition();
    associated.angleDeg = minionPosition.AngleDegTo(alienPosition) + MINION_ANGLEDEG_ADJUST;
}

void Minion::Render () {}

void Minion::Shoot (Vec2 target) {
    Vec2 minionPosition = associated.box.GetPosition();
    float angle = minionPosition.AngleTo(target);

    GameObject* bullet = new GameObject(MINION_BULLET_LAYER, MINION_BULLET_LABEL);
    bullet->AddComponent(
        new Bullet(
            *bullet, MINION_BULLET_SPRITE,
            angle, MINION_BULLET_SPEED, MINION_BULLET_RANGE,
            MINION_BULLET_DAMAGE,
            MINION_BULLET_FRAME_COUNT, MINION_BULLET_FRAME_TIME, MINION_BULLET_FRAME_ONESHOT,
            MINION_BULLET_TARGETS,
            MINION_BULLET_SOUND_SHOT, MINION_BULLET_SOUND_HIT
        )
    );
    bullet->box.SetPosition(minionPosition);
    Game::GetInstance().GetCurrentState().AddObject(bullet);
}

void Minion::ExplodeAnimation () {
    State& state = Game::GetInstance().GetCurrentState();

    GameObject* explosion = new GameObject(MINION_DEATH_LAYER, MINION_DEATH_LABEL);
    explosion->AddComponent(
        new Sprite(
            *explosion, MINION_DEATH_SPRITE,
            MINION_DEATH_FRAME_COUNT, MINION_DEATH_FRAME_TIME,
            MINION_DEATH_FRAME_ONESHOT, MINION_DEATH_SELFDESTRUCTION
        )
    );
    explosion->box.SetPosition(associated.box.GetPosition());
    state.AddObject(explosion);

    if (not playDeathSound) return;
    GameObject* boom = new GameObject();
    Sound* explosionSound = new Sound(*boom, MINION_DEATH_SOUND);
    boom->AddComponent(explosionSound);
    state.AddObject(boom);
    explosionSound->Play(MINION_DEATH_SOUND_TIMES, MINION_DEATH_SELFDESTRUCTION);
}

void Minion::NotifyCollision (GameObject& other) {
    Bullet* bullet = (Bullet*)other.GetComponent("Bullet");
    if ((bullet != nullptr) and bullet->IsAimingAt(MINION_LABEL)) {
        damageTaken = bullet->GetDamage();
        return;
    }
    PenguinCannon* playerc = (PenguinCannon*)other.GetComponent("PenguinCannon");
    if (playerc != nullptr) {
        damageTaken = playerc->GetHP();
        return;
    }
    PenguinBody* playerb = (PenguinBody*)other.GetComponent("PenguinBody");
    if (playerb != nullptr) {
        damageTaken = playerb->GetHP();
        return;
    }
}

Vec2 Minion::GetPosition () {
    return associated.box.GetPosition();
}

int Minion::GetHP () {
    return hp;
}

bool Minion::IsDead () {
    return (hp <= 0);
}

bool Minion::Is (std::string type) {
    return (type == "Minion");
}