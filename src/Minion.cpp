#include "Minion.h"
#include "Game.h"
#include "Sprite.h"

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

    } else {
        Vec2 alienPos;
        Vec2 minionPos;

        arc += PI/4 * dt;
        alienPos = alienCenter.lock()->box.GetCenter();
        minionPos = alienPos + Vec2(120,0).Rotate(arc);
        associated.box.SetPosition(minionPos.x, minionPos.y);
    }
}

void Minion::Render () {}

bool Minion::Is (std::string type) {
    return (type == "Minion");
}