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
    // GameObject* pcannonObj = new GameObject(PENGUINC_LAYER, PENGUINB_LABEL);
    // pcannonObj->AddComponent(new PenguinCannon(*pcannonObj, associated));
    // pcannon = Game::GetInstance().GetCurrentState().AddObject(pcannonObj);
    rotationRadSpeed = Deg2Rad(PENGUINB_ROTATION_SPEED);

    // sylar's extra positioning
    position = associated.box.GetCenter();
    arcPlacement = Vec2(PENGUINB_ARC_DISTANCE) * (PI*2);
    center = position + arcPlacement;
    associated.box.SetPosition(center);
    deltaAngle = 0.0f;
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
        // pcannon.lock()->RequestDelete();
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
        deltaAngle = angle;     // sylar's extra positioning
    }
    if (input.IsKeyDown(KEY_D)) {
        angle += rotationRadSpeed * dt;
        associated.angleDeg = Rad2Deg(angle);
        deltaAngle = angle;     // sylar's extra positioning
    }
    
    speed = Vec2().DirectionFrom(angle) * linearSpeed;
    Vec2 displacement = speed * dt;
    associated.box.Translate(displacement);
    position += displacement;   // sylar's extra positioning

    Rect tilemapLimits(((StageState&)Game::GetInstance().GetCurrentState()).GetGameMapLimits());
    
    if (position.x < tilemapLimits.x) {
        // associated.box.x = tilemapLimits.x;              // idj's original positioning
        associated.box.x -= (position.x - tilemapLimits.x); // sylar's extra positioning
        position.x = tilemapLimits.x;                       // sylar's extra positioning
    } else if (position.x > tilemapLimits.w) {
        // associated.box.x = tilemapLimits.w;              // idj's original positioning
        associated.box.x -= (position.x - tilemapLimits.w); // sylar's extra positioning
        position.x = tilemapLimits.w;                       // sylar's extra positioning
    } if (position.y < tilemapLimits.y) {
        // associated.box.y = tilemapLimits.y;              // idj's original positioning
        associated.box.y -= (position.y - tilemapLimits.y); // sylar's extra positioning
        position.y = tilemapLimits.y;                       // sylar's extra positioning
    } else if (position.y > tilemapLimits.h) {
        // associated.box.y = tilemapLimits.h;              // idj's original positioning
        associated.box.y -= (position.y - tilemapLimits.h); // sylar's extra positioning
        position.y = tilemapLimits.h;                       // sylar's extra positioning
    }

    // sylar's extra positioning
    if (deltaAngle != 0.0f) {
        arcDisplacement = arcPlacement.Rotate(deltaAngle);
        center = position + arcDisplacement;
        associated.box.SetPosition(center);
        deltaAngle = 0.0f;
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
    explosion->box.SetPosition(position);
    state.AddObject(explosion);

    GameObject* boom = new GameObject();
    Sound* explosionSound = new Sound(*boom, PENGUINB_DEATH_SOUND);
    boom->AddComponent(explosionSound);
    state.AddObject(boom);
    explosionSound->Play(PENGUINB_DEATH_SOUND_TIMES, PENGUINB_DEATH_SELFDESTRUCTION);
}

// sylar's extra positioning
Vec2 PenguinBody::GetPosition () {
    return position;
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