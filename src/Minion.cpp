#include "Minion.h"
#include "Game.h"
#include "Sprite.h"
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
        float alienScale = ((Sprite*)alienCenter.lock()->GetComponent("Sprite"))->GetScale().x;
        Vec2 minionDistance = Vec2(MINION_ARC_DISTANCE) * alienScale;
        Vec2 minionPlacement = alienPosition + minionDistance.Rotate(arc);
        associated.box.SetPosition(minionPlacement);

        Vec2 minionPosition = associated.box.GetCenter();
        associated.angleDeg = minionPosition.AngleDegTo(alienPosition) + MINION_ANGLEDEG_ADJUST;
    }
}

void Minion::Render () {}

void Minion::Shoot (Vec2 target) {
    Vec2 minionPosition = associated.box.GetCenter();
    float angle = minionPosition.AngleTo(target);
    float distance = minionPosition.DistanceTo(target);

    GameObject* bullet = new GameObject();
    bullet->AddComponent(
        new Bullet(
            *bullet, MINION_BULLET_SPRITE,
            angle, MINION_BULLET_SPEED, distance,
            MINION_BULLET_DAMAGE
        )
    );
    bullet->box.SetPosition(minionPosition);
    Game::GetInstance().GetState().AddObject(bullet);
}

bool Minion::Is (std::string type) {
    return (type == "Minion");
}

Vec2 Minion::GetPosition () {
    return associated.box.GetCenter();
}