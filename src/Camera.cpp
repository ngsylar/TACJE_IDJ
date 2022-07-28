#include "Camera.h"
#include "InputManager.h"

GameObject* Camera::focus = nullptr;
Vec2 Camera::pos, Camera::speed;

void Camera::Follow (GameObject* newFocus) {
    focus = newFocus;
}

void Camera::Unfollow () {
    focus = nullptr;
}

void Camera::Update (float dt) {
    InputManager& input = InputManager::GetInstance();

    if (focus) {
        pos = focus->box.GetCenter();
    } else {

        if (input.IsKeyDown(KEY_ARROW_UP) or input.IsKeyDown(KEY_W)) {
            speed.y = -1;
        }
        if (input.IsKeyDown(KEY_ARROW_DOWN) or input.IsKeyDown(KEY_S)) {
            speed.y = 1;
        }
        if (input.IsKeyDown(KEY_ARROW_LEFT) or input.IsKeyDown(KEY_A)) {
            speed.x = -1;
        }
        if (input.IsKeyDown(KEY_ARROW_RIGHT) or input.IsKeyDown(KEY_D)) {
            speed.x = 1;
        }
        if (speed.x and speed.y) {
            speed.Normalize();
        }
        pos += speed * CAMERA_SPEED * dt;
    }

    speed.x = 0;
    speed.y = 0;
}