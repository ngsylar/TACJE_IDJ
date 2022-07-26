#include "Minion.h"
#include "Game.h"
#include "Sprite.h"
#include "Bullet.h"

Minion::Minion (
    GameObject& associated,
    GameObject& alienCenter,
    float arcOffsetDeg
): Component(associated) {

    Sprite* sprite = new Sprite(associated, MINION_SPR);
    associated.AddComponent(sprite);

    this->alienCenter = Game::GetInstance().GetState().GetObjectPtr(&alienCenter);
    arc = arcOffsetDeg;
}

void Minion::Update (float dt) {
    if (alienCenter.expired()) {
        associated.RequestDelete();
        return;
    }
    else {
        arc += PI * MINION_ARC_SPEED * dt;
        Vec2 alienPosition = alienCenter.lock()->box.GetCenter();
        Vec2 minionPosition = alienPosition + Vec2(MINION_ARC_DISTANCE).Rotate(arc);
        associated.box.SetPosition(minionPosition);
    }
}

void Minion::Render () {}

bool Minion::Is (std::string type) {
    return (type == "Minion");
}

void Minion::Shoot (Vec2 target) {
    Vec2 minionPosition = associated.box.GetCenter();
    float angle = minionPosition.AngleTo(target);
    float distance = minionPosition.DistanceTo(target);

    GameObject* bullet = new GameObject();
    Bullet* bulletRaw = new Bullet(*bullet, angle, BULLET1_SPEED, BULLET1_DAMAGE, distance, BULLET1_SPR);
    bullet->AddComponent(bulletRaw);
    bullet->box.SetPosition(minionPosition);
    Game::GetInstance().GetState().AddObject(bullet);
}