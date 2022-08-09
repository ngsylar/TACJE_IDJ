#include "Bullet.h"
#include "Sprite.h"

Bullet::Bullet (
    GameObject& associated, std::string spriteName,
    float angle, float linearSpeed, float maxDistance,
    int damage,
    int spriteFrameCount, float spriteFrameTime
): Component(associated) {

    Sprite* sprite = new Sprite(
        associated, spriteName, spriteFrameCount, spriteFrameTime
    );
    associated.AddComponent(sprite);
    associated.angleDeg = Rad2Deg(angle);

    speed = Vec2().DirectionFrom(angle) * linearSpeed;
    this->damage = damage;
    this->distanceLeft = maxDistance;
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

bool Bullet::Is (std::string type) {
    return (type == "Bullet");
}

int Bullet::GetDamage () {
    return damage;
}