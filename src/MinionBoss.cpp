#include "GentooEngine.h"
#include "MinionBoss.h"
#include "Alien.h"
#include "Bullet.h"

MinionBoss::MinionBoss (
    GameObject& associated, GameObject& alienCenter, float arcOffsetDeg
): Minion(associated, alienCenter, arcOffsetDeg) {
    still = false;
}

void MinionBoss::Start () {
    sprite->Open(MINION_BOSS_SPRITE);
    int rangeStart = MINION_SCALE_MIN * 100;
    int scaleMod = ((MINION_SCALE_MAX - MINION_SCALE_MIN) * 100) + 1;
    sprite->SetScale((float)((rand() % scaleMod) + rangeStart) / 100.0f);
    
    hp = sprite->GetScale().x * MINION_BOSS_HP_MODIFIER;
    damageTaken = 0;

    Vec2 alienPosition = alienCenter.lock()->box.GetPosition();
    float alienScale = ((Alien*)alienCenter.lock()->GetComponent("Alien"))->GetScale().x;
    Vec2 arcRadius = Vec2(MINION_ARC_RADIUS) * alienScale;
    Vec2 minionPosition = alienPosition + arcRadius.Rotate(-arc);
    associated.box.SetPosition(minionPosition);
}

void MinionBoss::Update (float dt) {
    if (alienCenter.expired()) {
        ExplodeAnimation();
        associated.RequestDelete();
        return;
    }
    if (damageTaken > 0) {
        hp -= damageTaken;
        damageTaken = 0;
    }
    if (hp <= 0) {
        return;
    }

    if (still) return;

    arc += PI * MINION_ARC_SPEED * dt;
    Vec2 alienPosition = alienCenter.lock()->box.GetPosition();
    float alienScale = ((Alien*)alienCenter.lock()->GetComponent("Alien"))->GetScale().x;
    Vec2 arcRadius = Vec2(MINION_ARC_RADIUS) * alienScale;
    associated.box.RotateAround(alienPosition, arcRadius, -arc);

    Vec2 minionPosition = associated.box.GetPosition();
    associated.angleDeg = minionPosition.AngleDegTo(alienPosition) + MINION_ANGLEDEG_ADJUST;
}

void MinionBoss::Shoot (Vec2 target, float bulletSpeed) {
    Vec2 minionPosition = associated.box.GetPosition();
    Vec2 radius(MINION_BOSS_BULLET_OFFSET);
    float angle = minionPosition.AngleTo(target);

    GameObject* bullet = new GameObject(MINION_BULLET_LAYER, MINION_BULLET_LABEL);
    bullet->AddComponent(
        new Bullet(
            *bullet, MINION_BOSS_BULLET_SPRITE,
            angle, bulletSpeed, MINION_BULLET_RANGE,
            MINION_BULLET_DAMAGE,
            MINION_BULLET_FRAME_COUNT, MINION_BULLET_FRAME_TIME, MINION_BULLET_FRAME_ONESHOT,
            MINION_BULLET_TARGETS,
            MINION_BULLET_SOUND_SHOT, MINION_BULLET_SOUND_HIT
        )
    );
    bullet->box.RotateAround(minionPosition, radius, angle);
    Game::GetInstance().GetCurrentState().AddObject(bullet);
}

void MinionBoss::ExplodeAnimation () {
    State& state = Game::GetInstance().GetCurrentState();

    GameObject* explosion = new GameObject(MINION_DEATH_LAYER, MINION_DEATH_LABEL);
    explosion->AddComponent(
        new Sprite(
            *explosion, MINION_BOSS_DEATH_SPRITE,
            MINION_DEATH_FRAME_COUNT, MINION_DEATH_FRAME_TIME,
            MINION_DEATH_FRAME_ONESHOT, MINION_DEATH_SELFDESTRUCTION
        )
    );
    explosion->box.SetPosition(associated.box.GetPosition());
    state.AddObject(explosion);
    
    GameObject* boom = new GameObject();
    Sound* explosionSound = new Sound(*boom, MINION_DEATH_SOUND);
    boom->AddComponent(explosionSound);
    state.AddObject(boom);
    explosionSound->Play(MINION_DEATH_SOUND_TIMES, MINION_DEATH_SELFDESTRUCTION);
}