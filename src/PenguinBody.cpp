#include "GentooEngine.h"
#include "StageState.h"
#include "PenguinBody.h"
#include "PenguinCannon.h"
#include "Alien.h"
#include "Minion.h"
#include "Bullet.h"

PenguinBody::PenguinBody (GameObject& associated): Component(associated) {

    Sprite* sprite = new Sprite(associated, PENGUINB_SPRITE);
    associated.AddComponent(sprite);
    associated.box.offset = Vec2(PENGUINB_CENTER_OFFSET);   // sylar's extra positioning

    Collider* collider = new Collider(associated);
    associated.AddComponent(collider);

    hp = PENGUINB_START_HP;
    damageTaken = 0;

    linearSpeed = 0.0f;
    angle = 0.0f;
}

PenguinBody::~PenguinBody () {
    Camera::Unfollow();
}

void PenguinBody::Start () {
    GameObject* pcannonObj = new GameObject(PENGUINC_LAYER, PENGUINB_LABEL);
    pcannonObj->AddComponent(new PenguinCannon(*pcannonObj, associated));
    pcannon = Game::GetInstance().GetCurrentState().AddObject(pcannonObj);
    rotationRadSpeed = Deg2Rad(PENGUINB_ROTATION_SPEED);

    stageLimits = Rect(
        ((StageState&)Game::GetInstance().GetCurrentState()).GetGameMapLimits()
    );
}

void PenguinBody::Update (float dt) {
    InputManager& input = InputManager::GetInstance();

    if (damageTaken > 0) {
        hp -= damageTaken;
        damageTaken = 0;
        // SDL_Log("Player %d", hp);    // remover linha
    }
    if (hp <= 0) {
        ExplodeAnimation();
        associated.RequestDelete();
        pcannon.lock()->RequestDelete();
        return;
    }

    if (input.IsKeyDown(KEY_W)) {
        if (linearSpeed < PENGUINB_MAX_SPEED) {
            linearSpeed += PENGUINB_ACCELERATION * dt;
        } else linearSpeed = PENGUINB_MAX_SPEED;
    }
    if (input.IsKeyDown(KEY_S)) {
        if (linearSpeed > (-PENGUINB_MAX_SPEED*0.5f)) {
            linearSpeed -= (PENGUINB_ACCELERATION*0.5) * dt;
        } else linearSpeed = (-PENGUINB_MAX_SPEED*0.5f);
    }
    if (input.IsKeyDown(KEY_A)) {
        angle -= rotationRadSpeed * dt;
        associated.angleDeg = Rad2Deg(angle);
    }
    if (input.IsKeyDown(KEY_D)) {
        angle += rotationRadSpeed * dt;
        associated.angleDeg = Rad2Deg(angle);
    }
    
    speed = Vec2().DirectionFrom(angle) * linearSpeed;
    Vec2 displacement = speed * dt;
    associated.box.Translate(displacement);

    if (associated.box.x < stageLimits.x) {
        associated.box.x = stageLimits.x;
    } else if (associated.box.x > stageLimits.w) {
        associated.box.x = stageLimits.w;
    } if (associated.box.y < stageLimits.y) {
        associated.box.y = stageLimits.y;
    } else if (associated.box.y > stageLimits.h) {
        associated.box.y = stageLimits.h;
    }
}

void PenguinBody::Render () {}

int PenguinBody::GetHP () {
    return hp;
}

void PenguinBody::ExplodeAnimation () {
    State& state = Game::GetInstance().GetCurrentState();

    GameObject* explosion = new GameObject(PENGUINB_DEATH_LAYER, PENGUINB_DEATH_LABEL);
    explosion->AddComponent(
        new Sprite(
            *explosion, PENGUINB_DEATH_SPRITE,
            PENGUINB_DEATH_FRAME_COUNT, PENGUINB_DEATH_FRAME_TIME,
            PENGUINB_DEATH_FRAME_ONESHOT, PENGUINB_DEATH_SELFDESTRUCTION
        )
    );
    explosion->box.SetPosition(associated.box.GetPosition());
    state.AddObject(explosion);

    GameObject* boom = new GameObject();
    Sound* explosionSound = new Sound(*boom, PENGUINB_DEATH_SOUND);
    boom->AddComponent(explosionSound);
    state.AddObject(boom);
    explosionSound->Play(PENGUINB_DEATH_SOUND_TIMES, PENGUINB_DEATH_SELFDESTRUCTION);
}

void PenguinBody::NotifyCollision (GameObject& other) {
    Bullet* bullet = (Bullet*)other.GetComponent("Bullet");
    if ((bullet != nullptr) and bullet->IsAimingAt(PENGUINB_LABEL)) {
        damageTaken = bullet->GetDamage();
        return;
    }
    Minion* minion = (Minion*)other.GetComponent("Minion");
    if (minion != nullptr) {
        damageTaken = minion->GetHP();
        return;
    }
    Alien* alien = (Alien*)other.GetComponent("Alien");
    if (alien != nullptr) {
        damageTaken = hp;
        return;
    }
}

bool PenguinBody::Is (std::string type) {
    return (type == "PenguinBody");
}