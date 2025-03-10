#include "Bullet.h"
#include "Novice.h"

Bullet::Bullet() {
    posX_ = 0;
    posY_ = 0;
    speed_ = 14;
    rad_ = 16;
    isShot_ = false;
    damage_ = 1;
}

void Bullet::Update() {
    if (isShot_) {
        posX_ += speed_;
        if (posX_ >= 1300) {
            isShot_ = false;
        }
    } 
}

void Bullet::Draw() {
    if (isShot_) {
        Novice::DrawBox(posX_, posY_, rad_, rad_, 0.0f, WHITE, kFillModeWireFrame);
    }
}
