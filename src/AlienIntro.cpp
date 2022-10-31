#include "GentooEngine.h"
#include "AlienIntro.h"

AlienIntro::AlienIntro (
    GameObject& associated, int minionCount, EnemyType type
): Component(associated) {
    this->type = type;

    if (type == BOSS)
        sprite = new Sprite(associated, ALIEN_BOSS_SPRITE);
    else
        sprite = new Sprite(associated, ALIEN_SPRITE);

    associated.AddComponent(sprite);
    
    sprite->SetScale(0.0f);
    scale = 0.0f;

    this->minionCount = minionCount;
}

void AlienIntro::Update (float dt) {
    associated.angleDeg += (ALIEN_ROTATION_SPEED * dt);

    if (scale < 1.0f) {
        scale += 0.25f * dt;
        sprite->SetScale(scale);
        return;
    }

    GenerateNPC();
}

void AlienIntro::GenerateNPC () {
    GameObject* alien = new GameObject(ALIEN_LAYER, ALIEN_LABEL);

    if (type == BOSS)
        alien->AddComponent(new AlienBoss(*alien, minionCount));
    else
        alien->AddComponent(new Alien(*alien, minionCount));
    
    alien->box.SetPosition(associated.box.GetPosition());
    alien->angleDeg = associated.angleDeg;

    Game::GetInstance().GetCurrentState().AddObject(alien);
    associated.RequestDelete();
}

bool AlienIntro::Is (std::string type) {
    return (type == "AlienIntro");
}