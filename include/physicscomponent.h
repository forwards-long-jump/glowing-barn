#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#include "component.h"
#include "hitboxcomponent.h"

class PhysicsComponent : public Component
{
public:
    PhysicsComponent(QString name_ = "PhysicsComponent", float accSpeed_ = 1., float jumpSpeed_ = -5., float g_ = 0.5, float friction_ = 0.9);

    void update() override;
    void handleCollision(HitboxComponent *hitbox);

    void setLeft(bool left_) {left = left_;}
    void setRight(bool right_) {right = right_;}
    void jump() {dy += jumpSpeed; onGround = false;}

    void setAccSpeed(float accSpeed_) {accSpeed = accSpeed_;}
    void setFriction(float friction_) {friction = friction_;}
    void disableGravityForTick();
    void setJumpSpeed(float jumpSpeed_) {jumpSpeed = jumpSpeed_;}
    void setG(float g_) {g = g_;}

    bool isFalling() const {return dy > 0;}
    bool isOnGround() const {return onGround;}
    bool hasZeroSpeed() const {return dx > - 0.5 && dx < 0.5;}

private:
    float dx;
    float dy;
    float accSpeed;
    float jumpSpeed;
    float g;
    float friction;

    bool onGround = true;

    bool left;
    bool right;
    bool ignoreGravityForTick;
};

#endif // PHYSICSCOMPONENT_H
