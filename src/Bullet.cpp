#include "Bullet.h"
#include "Collider.h"
#include "Sprite.h"
#include "Sound.h"

Bullet::Bullet (
    GameObject& associated, std::string spriteName,
    float angle, float linearSpeed, float maxDistance,
    int damage,
    int frameCount, float frameTime, bool framesOneshot,
    std::vector<std::string> targetLabels,
    std::string hitSoundFilename
): Component(associated) {

    Sprite* sprite = new Sprite(
        associated, spriteName, frameCount, frameTime, framesOneshot
    );
    associated.AddComponent(sprite);
    associated.angleDeg = Rad2Deg(angle);

    Collider* collider = new Collider(associated);
    associated.AddComponent(collider);

    speed = Vec2().DirectionFrom(angle) * linearSpeed;
    this->distanceLeft = maxDistance;

    targets = targetLabels;
    this->damage = damage;

    this->hitSoundFilename = hitSoundFilename;
}

void Bullet::Update (float dt) {
    if (distanceLeft > 0) {
        Vec2 displacement = speed * dt;
        associated.box.Translate(displacement);
        distanceLeft -= displacement.Magnitude();
    } else {
        PlayHitSound();
        associated.RequestDelete();
    }
}

void Bullet::Render () {}

bool Bullet::IsAimingAt (std::string targetLabel) {
    for (int i=0; i < (int)targets.size(); i++) {
        if (targets[i] == targetLabel)
            return true;
    }
    return false;
}

int Bullet::GetDamage () {
    return damage;
}

void Bullet::PlayHitSound () {
    if (hitSoundFilename.empty())
        return;

    GameObject* hit = new GameObject();
    Sound* hitSound = new Sound(*hit, hitSoundFilename);
    hit->AddComponent(hitSound);
    hitSound->Play(BULLET_HIT_SOUND_TIMES, BULLET_HIT_SELFDESTRUCTION);
}

void Bullet::NotifyCollision (GameObject& other) {
    if (IsAimingAt(other.label)) {
        PlayHitSound();
        associated.RequestDelete();
    }
}

bool Bullet::Is (std::string type) {
    return (type == "Bullet");
}