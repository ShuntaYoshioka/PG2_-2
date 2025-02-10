#pragma once
#include "Bullet.h"
class Player
{

private:

	//判定用
	int posX_;
	int posY_;
	int speedX_;
	int speedY_;
	int radius_;
	float slope_;

	int hp_;

	int playerTextureHandle_;

	//回転用
	float topLeftX_, topLeftY_;
	float topRightX_, topRightY_;
	float bottomLeftX_, bottomLeftY_;
	float bottomRightX_, bottomRightY_;

	float halfSize_;
	float radian_;
	float cosTheta_;
	float sinTheta_;

public:
	//コンストラクタ

	int isAlive_;
	Player(int posX, int posY, int speedX, int speedY);
	~Player();

	Bullet bullets_[25];

	//ゲッター
	int GetPosX() const { return posX_; }

	void SetPosX(int posX) { posX_ = posX; }

	int GetPosY() const { return posY_; }

	void SetPosY(int posY) { posY_ = posY; }


	int GetSpeedX() const { return speedX_; }

	void SetSpeedX(int speedX) { speedX_ = speedX; }

	int GetSpeedY() const { return speedY_; }

	void SetSpeedY(int speedY) { speedY_ = speedY; }

	int GetRadius() const { return radius_; }

	int GetHP() const { return hp_; }

	void TakeDamage(int damage);

	void Update();
	void Move(const char* keys);
	void Draw();

};

