#include "Alien.h"
#include "Game.h"
#include "Camera.h"
#include "Collider.h"
#include "Sound.h"
#include "Minion.h"
#include "PenguinBody.h"
#include "PenguinCannon.h"
#include "Bullet.h"

Alien::Alien (GameObject& associated, int nMinions): Component(associated) {

    sprite = new Sprite(associated, ALIEN_SPRITE);
    associated.AddComponent(sprite);
    Collider* collider = new Collider(associated);
    associated.AddComponent(collider);

    this->nMinions = nMinions;
    hp = ALIEN_START_HP;
    damageTaken = 0;

    restTimer = Timer(ALIEN_MOVEMENT_COOLDOWN, ALIEN_TIMER_START);
    cooldown = Timer(ALIEN_SHOT_COOLDOWN, ALIEN_TIMER_START);
    state = RESTING;
}

Alien::~Alien () {
    if (not Game::GetInstance().GetState().QuitRequested()) {
        for (int i=0; i < (int)minionArray.size(); i++)
            ((Minion*)minionArray[i].lock()->GetComponent("Minion"))->ExplodeAnimation();
    }
    minionArray.clear();
}

void Alien::Start () {
    GameObject* minion;
    float minionArcPlacement;

    for (int i=0; i < nMinions; i++) {
        minion = new GameObject(MINION_LAYER, MINION_LABEL);
        minionArcPlacement = (float)i*((PI*2)/nMinions);
        minion->AddComponent(new Minion(*minion, associated, minionArcPlacement));
        minionArray.push_back(Game::GetInstance().GetState().AddObject(minion));
    }
    penguin = Game::GetInstance().GetState().GetObjectPtr(ALIEN_FOE_LABEL);
}

void Alien::Update (float dt) {
    Minion* minion;
    
    if (hp <= 0) {
        ExplodeAnimation();
        associated.RequestDelete();
        return;
    }

    for (int i=(int)minionArray.size()-1; i >= 0; i--) {
        minion = (Minion*)minionArray[i].lock()->GetComponent("Minion");
        if (minion->IsDead()) {
            minion->ExplodeAnimation();
            minionArray[i].lock()->RequestDelete();
            minionArray.erase(minionArray.begin()+i);
        }
    }

    if (penguin.expired()) {
        state = SLEEPING;
    }
    
    else if (state == RESTING) {
        cooldown.Update(dt);
        if (cooldown.IsOver() and (not minionArray.empty())) {
            float targetDistance = 999999.0f;
            float minionDistance;
            int minionShooterId;

            target = penguin.lock()->box.GetCenter();

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
            cooldown.Reset();
        }

        restTimer.Update(dt);
        if (restTimer.IsOver()) {
            target = penguin.lock()->box.GetCenter();
            restTimer.Reset();
            state = MOVING;
        }
    }
    else if (state == MOVING) {
        Vec2 currentPosition = associated.box.GetCenter();

        if (currentPosition.DistanceTo(target) > ALIEN_MINIMUM_DISTANCE) {
            float targetAngle = currentPosition.AngleTo(target);
            speed = currentPosition.DirectionFrom(targetAngle);
            associated.box.Translate(speed * ALIEN_LINEAR_SPEED * dt);
        } else {
            associated.box.SetPosition(target);
            speed = Vec2();
            state = RESTING;
        }
    }

    associated.angleDeg += (ALIEN_ROTATION_SPEED * dt);
    BreathAnimation(dt);    // sylar's alien breath extra effects
}

void Alien::Render () {}

int Alien::GetHP () {
    return hp;
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
    State& gameState = Game::GetInstance().GetState();

    GameObject* explosion = new GameObject(ALIEN_DEATH_LAYER, ALIEN_DEATH_LABEL);
    explosion->AddComponent(
        new Sprite(
            *explosion, ALIEN_DEATH_SPRITE,
            ALIEN_DEATH_FRAME_COUNT, ALIEN_DEATH_FRAME_TIME,
            ALIEN_DEATH_FRAME_ONESHOT, ALIEN_DEATH_SELFDESTRUCTION
        )
    );
    explosion->box.SetPosition(associated.box.GetCenter());
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

bool Alien::Is (std::string type) {
    return (type == "Alien");
}