#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#include "component.h"
#include "squarehitboxcomponent.h"

class PhysicsComponent : public Component
{
public:
    PhysicsComponent(float accSpeed_ = 1.0, float maxHSpeed_ = 4.5, float friction_ = 0.8, float jumpSpeed_ = -10., float g_ = 0.7, float maxVSpeed_ = 10., QString name_ = "PhysicsComponent");

    void update() override;
    void handleCollision(SquareHitboxComponent *hitbox);

    void setLeft(bool left_) {left = left_;}
    void setRight(bool right_) {right = right_;}
    void jump() {dy = jumpSpeed; onGround = false;}
    void setSpeed(float dx_, float dy_) {dx = dx_; dy = dy_;}

    void setAccSpeed(float accSpeed_) {accSpeed = accSpeed_;}
    void setFriction(float friction_) {friction = friction_;}
    void disablePhysicsForTick();
    void setJumpSpeed(float jumpSpeed_) {jumpSpeed = jumpSpeed_;}
    void setG(float g_) {g = g_;}

    bool isFalling() const {return dy > 0;}
    bool isOnGround() const {return onGround;}
    bool hasZeroSpeed() const {return dx > - 0.5 && dx < 0.5;}

private:
    float dx;
    float dy;

    float accSpeed;
    float maxHSpeed;
    float friction;
    float jumpSpeed;
    float g;
    float maxVSpeed;

    bool onGround = true;

    bool left;
    bool right;
    bool ignorePhysicsForTick;
};

#endif // PHYSICSCOMPONENT_H
