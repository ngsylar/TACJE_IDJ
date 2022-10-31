#include "GentooEngine.h"
#include "MinionIntro.h"
#include "Alien.h"

MinionIntro::MinionIntro (
    GameObject& associated, GameObject& alienCenter, int arrayIndex,
    float arcOffsetDeg, float scale,
    EnemyType type
): Component(associated) {
    Sprite* sprite;

    this->alienCenter = Game::GetInstance().GetCurrentState().GetObjectPtr(&alienCenter);
    this->type = type;

    if (type == BOSS)
        sprite = new Sprite(associated, MINION_BOSS_SPRITE);
    else
        sprite = new Sprite(associated, MINION_SPRITE);

    associated.AddComponent(sprite);
    
    this->scale = scale;
    arc = arcOffsetDeg;
}

void MinionIntro::Start () {
    Vec2 alienPosition = alienCenter.lock()->box.GetPosition();
    position = alienPosition + Vec2(MINION_ARC_RADIUS).Rotate(-arc);
    associated.angleDeg = position.AngleDegTo(alienPosition) + MINION_ANGLEDEG_ADJUST;
}

void MinionIntro::Update (float dt) {
    // usar o codigo de delocamento de enemyintro antigo aqui
    
    // associated.angleDeg += (ALIEN_ROTATION_SPEED * dt);

    // if (scale < 1.0f) {
    //     scale += 0.25f * dt;
    //     sprite->SetScale(scale);
    //     return;
    // }

    GenerateNPC();
}

void MinionIntro::GenerateNPC () {
    GameObject* minion = new GameObject(MINION_LAYER, MINION_LABEL);

    if (type == BOSS)
        minion->AddComponent(new MinionBoss(*minion, *alienCenter.lock(), arc));
    else
        minion->AddComponent(new Minion(*minion, *alienCenter.lock(), arc, scale));
    
    minion->box.SetPosition(associated.box.GetPosition());

    Alien* alien = (Alien*)alienCenter.lock()->GetComponent("Alien");
    alien->ReplaceMinion(minion, arrayIndex);
}

bool MinionIntro::Is (std::string type) {
    return (type == "MinionIntro");
}