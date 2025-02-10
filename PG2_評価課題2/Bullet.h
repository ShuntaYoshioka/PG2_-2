#pragma once
class Bullet
{
public:
	int posX_;
	int posY_;
	int speed_;
	int rad_;
	int isShot_;
	int damage_;

	Bullet();

	void Update();
	void Draw();
};
