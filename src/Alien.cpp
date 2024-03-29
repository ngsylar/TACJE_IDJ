#include "GentooEngine.h"
#include "GameData.h"
#include "Alien.h"
#include "Minion.h"
#include "Bullet.h"
#include "PenguinBody.h"
#include "PenguinCannon.h"

int Alien::alienCount = 0;

Alien::Alien (
    GameObject& associated, int minionCount, std::vector<float> minionScaleArray
): Component(associated) {
    sprite = new Sprite(associated, ALIEN_SPRITE);
    // associated.AddComponent(sprite);    // idj's original object rendering
    // associated.box.offset = Vec2(ALIEN_CENTER_OFFSET);  // sylar's extra positioning

    Collider* collider = new Collider(associated);
    associated.AddComponent(collider);
    
    hp = ALIEN_START_HP;
    damageTaken = 0;

    float startTime = ALIEN_SHOT_COOLDOWN + (ALIEN_TIMER_START * alienCount);
    restTimer = Timer(ALIEN_MOVEMENT_COOLDOWN, startTime);
    cooldown = Timer(ALIEN_SHOT_COOLDOWN, startTime);
    state = RESTING;

    alienCount++;

    this->minionCount = minionCount;
    while ((int)minionScaleArray.size() < minionCount)
        minionScaleArray.push_back(1.0f);
    this->minionScaleArray = minionScaleArray;
}

Alien::~Alien () {
    delete sprite;  // sylar's alien breath extra effects
    minionArray.clear();
    alienCount--;
    GameData::kills++;
}

void Alien::Start () {
    State& gameState = Game::GetInstance().GetCurrentState();
    penguin = gameState.GetObjectPtr(ALIEN_FOE_LABEL);
    GenerateMinions();
}

void Alien::Update (float dt) {
    if (damageTaken > 0) {
        hp -= damageTaken;
        damageTaken = 0;
        // SDL_Log("Alien %d", hp);     // remover linha
    }
    if (hp <= 0) {
        ExplodeAnimation();
        associated.RequestDelete();
        return;
    }
    CheckDeadMinions();

    // State Sleeping
    if (penguin.expired()) {
        state = SLEEPING;
    }
    // State Chasing
    else if (minionArray.empty()) {
        target = penguin.lock()->box.GetPosition();
        state = MOVING;
    }
    // State Resting/Shooting
    if (state == RESTING) {
        ActionRest(dt);
    }
    // State Moving
    else if (state == MOVING) {
        ActionMove(dt);
    }

    associated.angleDeg += (ALIEN_ROTATION_SPEED * dt);
    BreathAnimation(dt);    // sylar's alien breath extra effects
}

// sylar's alien breath extra effects
void Alien::Render () {
    sprite->RenderWithNoOffset(
        (int)associated.box.x - Camera::pos.x,
        (int)associated.box.y - Camera::pos.y
    );
}

void Alien::GenerateMinions () {
    State& gameState = Game::GetInstance().GetCurrentState();
    GameObject* minion;
    float minionArcPlacement;

    for (int i=0; i < minionCount; i++) {
        minion = new GameObject(MINION_LAYER, MINION_LABEL);
        minionArcPlacement = (float)i*((PI*2)/minionCount);
        minion->AddComponent(
            new Minion(*minion, associated, minionArcPlacement, minionScaleArray[i])
        );
        minionArray.push_back(gameState.AddObject(minion));
    }
}

void Alien::CheckDeadMinions () {
    Minion* minion;

    for (int i=(int)minionArray.size()-1; i >= 0; i--) {
        minion = (Minion*)minionArray[i].lock()->GetComponent("Minion");
        if (minion->IsDead()) {
            minion->ExplodeAnimation();
            minionArray[i].lock()->RequestDelete();
            minionArray.erase(minionArray.begin()+i);
        }
    }
}

void Alien::ActionRest (float dt) {
    cooldown.Update(dt);
    if (cooldown.IsOver() and (not minionArray.empty())) {
        ActionShoot();
        cooldown.Reset();
    }

    restTimer.Update(dt);
    if (restTimer.IsOver()) {
        target = penguin.lock()->box.GetPosition();
        restTimer.Reset();
        state = MOVING;
    }
}

void Alien::ActionShoot () {
    float targetDistance = 999999.0f;
    Minion* minion;
    float minionDistance;
    int minionShooterId;

    target = penguin.lock()->box.GetPosition();

    for (int i=0; i < (int)minionArray.size(); i++) {
        minion = (Minion*)minionArray[i].lock()->GetComponent("Minion");
        minionDistance = minion->GetPosition().DistanceTo(target);

        if (minionDistance < targetDistance) {
            targetDistance = minionDistance;
            minionShooterId = i;
        }
    }
    minion = (Minion*)minionArray[minionShooterId].lock()->GetComponent("Minion");
    minion->Shoot(target);
}

void Alien::ActionMove (float dt) {
    Vec2 currentPosition = associated.box.GetPosition();

    if (currentPosition.DistanceTo(target) > ALIEN_MINIMUM_DISPLACEMENT) {
        float targetAngle = currentPosition.AngleTo(target);
        speed = currentPosition.DirectionFrom(targetAngle);
        associated.box.Translate(speed * ALIEN_LINEAR_SPEED * dt);
    } else {
        associated.box.SetPosition(target);
        speed = Vec2();
        state = RESTING;
    }
}

// sylar's alien breath extra effects
void Alien::BreathAnimation (float dt) {
    float currentScale = sprite->GetScale().x;

    if (currentScale <= 1.0f)
        breathIn = true;
    else if (currentScale >= 1.06f)
        breathIn = false;

    if (breathIn) currentScale += (0.08f*dt);
    else currentScale -= (0.08f*dt);
    
    sprite->SetScale(currentScale);
}

void Alien::ExplodeAnimation () {
    State& gameState = Game::GetInstance().GetCurrentState();

    GameObject* explosion = new GameObject(ALIEN_DEATH_LAYER, ALIEN_DEATH_LABEL);
    explosion->AddComponent(
        new Sprite(
            *explosion, ALIEN_DEATH_SPRITE,
            ALIEN_DEATH_FRAME_COUNT, ALIEN_DEATH_FRAME_TIME,
            ALIEN_DEATH_FRAME_ONESHOT, ALIEN_DEATH_SELFDESTRUCTION
        )
    );
    explosion->box.SetPosition(associated.box.GetPosition());
    gameState.AddObject(explosion);

    GameObject* boom = new GameObject();
    Sound* explosionSound = new Sound(*boom, ALIEN_DEATH_SOUND);
    boom->AddComponent(explosionSound);
    gameState.AddObject(boom);
    explosionSound->Play(ALIEN_DEATH_SOUND_TIMES, ALIEN_DEATH_SELFDESTRUCTION);
}

void Alien::NotifyCollision (GameObject& other) {
    Bullet* bullet = (Bullet*)other.GetComponent("Bullet");
    if ((bullet != nullptr) and bullet->IsAimingAt(ALIEN_LABEL)) {
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

Vec2 Alien::GetScale () {
    return sprite->GetScale();
}

int Alien::GetHP () {
    return hp;
}

int Alien::GetAlienCount () {
    return alienCount;
}

bool Alien::Is (std::string type) {
    return (type == "Alien");
}