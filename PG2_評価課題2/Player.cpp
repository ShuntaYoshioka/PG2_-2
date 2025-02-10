#include "Player.h"
#include "Novice.h"
#include <cmath>

Player::Player(int posX, int posY, int speedX, int speedY)
{
    posX_ = posX;
    posY_ = posY;
    speedX_ = speedX;
    speedY_ = speedY;
    radius_ = 16;
    slope_  = 0.0f;
    hp_ = 3;

    playerTextureHandle_ = Novice::LoadTexture("./NoviceResources/white1x1.png");

    halfSize_ = 16.0f;
    radian_ = 0.0f;
    cosTheta_ = 1.0f;
    sinTheta_ = 0.0f;

    Update();
}

Player::~Player()
{
}

void Player::TakeDamage(int damage) {
    hp_ -= damage;
    if (hp_ <= 0) {
        hp_ = 0;
        // ゲームオーバー
    }
}

void Player::Move(const char* keys){
    //移動
    if (keys[DIK_W]) {
        posY_ -= speedY_;
    }
    if (keys[DIK_A]) {
        posX_ -= speedX_;
    }
    if (keys[DIK_S]) {
        posY_ += speedY_;
    }
    if (keys[DIK_D]) {
        posX_ += speedX_; 
    }

    //弾を発射
    if (keys[DIK_SPACE]) {
        for (int i = 0; i < 25; i++) {
            if (!bullets_[i].isShot_) { 
                bullets_[i].posX_ = posX_ + radius_;
                bullets_[i].posY_ = posY_ - radius_;
                bullets_[i].isShot_ = true; 
                break;
            }
        }
    }


    // 弾の更新
    for (int i = 0; i < 25; i++) {
        bullets_[i].Update();
    }
}

void Player::Update(){
    slope_ += 0.06f;
    radian_ = slope_;

    //三角関数
    cosTheta_ = cosf(radian_);
    sinTheta_ = sinf(radian_);

    //四隅の回転
    topLeftX_ = posX_ + (-halfSize_ * cosTheta_ - (-halfSize_) * sinTheta_);
    topLeftY_ = posY_ + (-halfSize_ * sinTheta_ + (-halfSize_) * cosTheta_);
    topRightX_ = posX_ + (halfSize_ * cosTheta_ - (-halfSize_) * sinTheta_);
    topRightY_ = posY_ + (halfSize_ * sinTheta_ + (-halfSize_) * cosTheta_);
    bottomLeftX_ = posX_ + (-halfSize_ * cosTheta_ - halfSize_ * sinTheta_);
    bottomLeftY_ = posY_ + (-halfSize_ * sinTheta_ + halfSize_ * cosTheta_);
    bottomRightX_ = posX_ + (halfSize_ * cosTheta_ - halfSize_ * sinTheta_);
    bottomRightY_ = posY_ + (halfSize_ * sinTheta_ + halfSize_ * cosTheta_);
}

void Player::Draw(){
    Novice::DrawQuad(
        static_cast<int>(topLeftX_), static_cast<int>(topLeftY_),
          static_cast<int>(topRightX_), static_cast<int>(topRightY_),
          static_cast<int>(bottomLeftX_), static_cast<int>(bottomLeftY_),
          static_cast<int>(bottomRightX_), static_cast<int> (bottomRightY_),
        0, 0, 64, 64,
        playerTextureHandle_,
        WHITE
    );

    //弾
    for (int i = 0; i < 25; i++) {
        bullets_[i].Draw();
    }
}
