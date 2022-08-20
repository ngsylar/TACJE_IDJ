#include "Bullet.h"
#include "Sprite.h"
#include "Collider.h"

Bullet::Bullet (
    GameObject& associated, std::string spriteName,
    float angle, float linearSpeed, float maxDistance,
    int damage,
    int spriteFrameCount, float spriteFrameTime,
    bool targetsPlayer
): Component(associated) {

    Sprite* sprite = new Sprite(
        associated, spriteName, spriteFrameCount, spriteFrameTime
    );
    associated.AddComponent(sprite);
    associated.angleDeg = Rad2Deg(angle);

    Collider* collider = new Collider(associated);
    associated.AddComponent(collider);

    speed = Vec2().DirectionFrom(angle) * linearSpeed;
    this->distanceLeft = maxDistance;

    this->damage = damage;
    this->targetsPlayer = targetsPlayer;
}

void Bullet::Update (float dt) {
    if (distanceLeft > 0) {
        Vec2 displacement = speed * dt;
        associated.box.Translate(displacement);
        distanceLeft -= displacement.Magnitude();
    } else {
        associated.RequestDelete();
    }
}

void Bullet::Render () {}

int Bullet::GetDamage () {
    return damage;
}

void Bullet::NotifyCollision (GameObject& other) {
    bool shootingPlayer = (targetsPlayer and (other.label == "Player"));
    bool shootingEnemy = (IsTargetingEnemy() and other.label == "Enemy");

    if (shootingPlayer or shootingEnemy) {
        associated.RequestDelete();
    }
}

bool Bullet::IsTargetingPlayer () {
    return targetsPlayer;
}

bool Bullet::IsTargetingEnemy () {
    return (not targetsPlayer);
}

bool Bullet::Is (std::string type) {
    return (type == "Bullet");
}