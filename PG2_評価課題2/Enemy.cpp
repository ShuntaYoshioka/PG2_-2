#include "Enemy.h"
#include <Novice.h>

Enemy::Enemy() : posX_(0), posY_(0), speedX_(0), speedY_(0), radius_(16), hp_(5) {
}

Enemy::Enemy(int posX, int posY, int speedX, int speedY) {
    posX_ = posX;
    posY_ = posY;
    speedX_ = speedX;
    speedY_ = speedY;
    radius_ = 16;
    hp_ = 5; 
}

Enemy::~Enemy() {
}

void Enemy::Update() {
    posX_ -= speedX_;
    if (posX_ + radius_ < 0) {
        posX_ = 1280 + radius_;
        posY_ = rand() % 720;
        hp_ = 5;
    }
}

void Enemy::Draw() {
    Novice::DrawEllipse(posX_, posY_, radius_, radius_, 0.0f, WHITE, kFillModeSolid);
}

