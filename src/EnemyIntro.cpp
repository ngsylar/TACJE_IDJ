#include "GentooEngine.h"
#include "EnemyIntro.h"

AlienIntro::AlienIntro (
    GameObject& associated, int minionCount, bool boss
): Component(associated) {
    this->minionCount = minionCount;
    this->boss = boss;

    if (boss) sprite = new Sprite(associated, ALIEN_BOSS_SPRITE);
    else sprite = new Sprite(associated, ALIEN_SPRITE);
    associated.AddComponent(sprite);
    sprite->SetScale(0.0f);
    scale = 0.0f;
}

void AlienIntro::Start () {
    State& gameState = Game::GetInstance().GetCurrentState();
    GameObject* minion;
    float minionArcPlacement;

    minionsReady = 0;
    for (int i=0; i < minionCount; i++) {
        minion = new GameObject(MINION_LAYER, MINION_LABEL);
        minionArcPlacement = (float)i*((PI*2)/minionCount);
        minion->AddComponent(new MinionIntro(*minion, associated, i, minionArcPlacement, boss));
        minionArray.push_back(gameState.AddObject(minion));
    }
    countdown.SetResetTime(0.75f);
}

void AlienIntro::Update (float dt) {
    associated.angleDeg += (ALIEN_ROTATION_SPEED * dt);

    if (scale < 1.0f) {
        scale += 0.25f * dt;
        sprite->SetScale(scale);
        return;
    }

    countdown.Update(dt);
    if (countdown.IsOver())
        GenerateNPC();
}

void AlienIntro::IncreaseReadyMinions () {
    minionsReady++;
}

void AlienIntro::GenerateNPC () {
    if (minionsReady != minionCount)
        return;

    std::vector<float> minionScaleArray;
    for (int i=0; i < minionCount; i++)
        minionScaleArray.push_back(
            ((MinionIntro*)minionArray[i].lock()->GetComponent("MinionIntro"))->GetScale()
        );

    GameObject* alien = new GameObject(ALIEN_LAYER, ALIEN_LABEL);
    if (boss) alien->AddComponent(new AlienBoss(*alien, ALIEN_MINION_COUNT));
    else alien->AddComponent(new Alien(*alien, ALIEN_MINION_COUNT, minionScaleArray));
    alien->box.SetPosition(associated.box.GetPosition());
    alien->angleDeg = associated.angleDeg;
    Game::GetInstance().GetCurrentState().AddObject(alien);
    associated.RequestDelete();
}

bool AlienIntro::Is (std::string type) {
    return (type == "AlienIntro");
}

MinionIntro::MinionIntro (
    GameObject& associated, GameObject& alienCenter, int index, float arcOffsetDeg, bool boss
): Component(associated) {

    this->alienCenter = Game::GetInstance().GetCurrentState().GetObjectPtr(&alienCenter);
    this->index = index;
    this->boss = boss;

    if (boss) sprite = new Sprite(associated, MINION_BOSS_SPRITE);
    else sprite = new Sprite(associated, MINION_SPRITE);
    associated.AddComponent(sprite);
    sprite->SetScale(0.0f);
    scale = 0.0f;

    int rangeStart = MINION_SCALE_MIN * 100;
    int scaleMod = ((MINION_SCALE_MAX - MINION_SCALE_MIN) * 100) + 1;
    desiredScale = (float)((rand() % scaleMod) + rangeStart) / 100.0f;

    arc = arcOffsetDeg;

    readyPosition = false;
    readyScale = false;
    ready = false;
}

void MinionIntro::Start () {
    Vec2 arcRadius(MINION_ARC_RADIUS);
    alienPosition = alienCenter.lock()->box.GetPosition();
    position = alienPosition + arcRadius.Rotate(-arc);
    associated.box.SetPosition(alienPosition);
    associated.angleDeg = position.AngleDegTo(alienPosition) + MINION_ANGLEDEG_ADJUST;
    countdown.SetResetTime(0.75f);
}

void MinionIntro::Update (float dt) {
    if (alienCenter.expired()) {
        associated.RequestDelete();
        return;
    }

    countdown.Update(dt);
    if (not countdown.IsOver())
        return;

    Vec2 currentPosition = associated.box.GetPosition();
    if (currentPosition.DistanceTo(position) > 1.0f) {
        float targetAngle = currentPosition.AngleTo(position);
        Vec2 speed = currentPosition.DirectionFrom(targetAngle);
        associated.box.Translate(speed * 30.0f * dt);
    } else readyPosition = true;

    if (scale < desiredScale) {
        scale += 0.25f * desiredScale * dt;
        sprite->SetScale(scale);
    } else readyScale = true;
    
    if ((not ready) and readyPosition and readyScale) {
        ((AlienIntro*)alienCenter.lock()->GetComponent("AlienIntro"))->IncreaseReadyMinions();
        ready = true;
    }
}

float MinionIntro::GetScale () {
    return scale;
}

bool MinionIntro::Is (std::string type) {
    return (type == "MinionIntro");
}