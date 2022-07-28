#include "Bullet.h"
#include "Sprite.h"

Bullet::Bullet (
    GameObject& associated,
    std::string spriteName,
    float angle,
    float speed,
    float maxDistance,
    int damage
): Component(associated) {

    Sprite* sprite = new Sprite(
        associated, spriteName,
        BULLET1_FRAME_COUNT, BULLET1_FRAME_TIME
    );
    associated.AddComponent(sprite);
    associated.angleDeg = angle * (180.0f/PI) + BULLET_ANGLEDEG_ADJUST;

    this->speed = Vec2().DirectionFrom(angle) * speed;
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