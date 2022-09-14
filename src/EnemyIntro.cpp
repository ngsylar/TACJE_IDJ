#include "GentooEngine.h"
#include "EnemyIntro.h"

AlienIntro::AlienIntro (
    GameObject& associated, int minionCount, bool boss
): Component(associated) {
    this->minionCount = minionCount;
    this->boss = boss;

    if (boss) {
        sprite = new Sprite(associated, ALIEN_BOSS_SPRITE);
    } else {
        sprite = new Sprite(associated, ALIEN_SPRITE);
    }
    associated.AddComponent(sprite);
    sprite->SetScale(0.0f);
    scale = 0.0f;
}

void AlienIntro::Start () {
    State& gameState = Game::GetInstance().GetCurrentState();
    GameObject* minion;
    float minionArcPlacement;

    for (int i=0; i < minionCount; i++) {
        minion = new GameObject(MINION_LAYER, MINION_LABEL);
        minionArcPlacement = (float)i*((PI*2)/minionCount);
        minion->AddComponent(new MinionIntro(*minion, associated, minionArcPlacement, boss));
        minionArray.push_back(gameState.AddObject(minion));
    }
    SDL_Log("here");
}

void AlienIntro::Update (float dt) {
    if (scale < 1.0f) {
        scale += 0.25f * dt;
        sprite->SetScale(scale);
    }
    // if (scale >= 0.75) {
    // }
}

void AlienIntro::Render () {}

bool AlienIntro::Is (std::string type) {
    return (type == "AlienIntro");
}

MinionIntro::MinionIntro (
    GameObject& associated, GameObject& alienCenter, float arcOffsetDeg, bool boss
): Component(associated) {

    this->alienCenter = Game::GetInstance().GetCurrentState().GetObjectPtr(&alienCenter);
    this->boss = boss;

    if (boss) {
        sprite = new Sprite(associated, MINION_BOSS_SPRITE);
    } else {
        sprite = new Sprite(associated, MINION_SPRITE);
    }
    associated.AddComponent(sprite);
    sprite->SetScale(0.0f);
    scale = 0.0f;

    int rangeStart = MINION_SCALE_MIN * 100;
    int scaleMod = ((MINION_SCALE_MAX - MINION_SCALE_MIN) * 100) + 1;
    desiredScale = (float)((rand() % scaleMod) + rangeStart) / 100.0f;

    arc = arcOffsetDeg;
}

void MinionIntro::Start () {
    Vec2 arcRadius(MINION_ARC_RADIUS);
    alienPosition = alienCenter.lock()->box.GetPosition();
    position = alienPosition + arcRadius.Rotate(-arc);
    associated.box.SetPosition(alienPosition);
    generator.SetResetTime(0.75f);
}

void MinionIntro::Update (float dt) {
    Vec2 currentPosition = associated.box.GetPosition();

    if (currentPosition.DistanceTo(position) > ALIEN_MINIMUM_DISPLACEMENT) {
        float targetAngle = currentPosition.AngleTo(position);
        Vec2 speed = currentPosition.DirectionFrom(targetAngle);
        associated.box.Translate(speed * 22.5f * dt);
    }

    generator.Update(dt);
    if (not generator.IsOver())
        return;

    if (scale < desiredScale) {
        scale += 0.25f * dt;
        sprite->SetScale(scale);
    }
}

void MinionIntro::Render () {}

bool MinionIntro::Is (std::string type) {
    return (type == "MinionIntro");
}