#pragma once
class Enemy
{
private:
    int posX_;
    int posY_;
    int speedX_;
    int speedY_;
    int radius_;
    int hp_;  

public:
    Enemy();
    Enemy(int posX, int posY, int speedX, int speedY);
    ~Enemy();

    void Update();
    void Draw();

    int GetPosX() const { return posX_; }
    int GetPosY() const { return posY_; }
    int GetRadius() const { return radius_; }
    int GetHP() const { return hp_; }

    void SetPosX(int posX) { posX_ = posX; }
    void SetPosY(int posY) { posY_ = posY; }
};
