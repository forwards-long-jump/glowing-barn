#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#include "component.h"

class PhysicsComponent : public Component
{
public:
    PhysicsComponent(QString name_ = "PhysicsComponent", float accSpeed_ = 1., float jumpSpeed_ = -20., float g_ = 0.1, float friction_ = 0.9);

    void update() override;

    void setLeft(bool left_) {left = left_;}
    void setRight(bool right_) {right = right_;}
    void jump() {dy += jumpSpeed;}

    void setAccSpeed(float accSpeed_) {accSpeed = accSpeed_;}
    void setFriction(float friction_) {friction = friction_;}
    void setJumpSpeed(float jumpSpeed_) {jumpSpeed = jumpSpeed_;}
    void setG(float g_) {g = g_;}

    bool isFalling() const {return dy > 0;}

private:
    float dx;
    float dy;
    float accSpeed;
    float jumpSpeed;
    float g;
    float friction;

    bool left;
    bool right;
};

#endif // PHYSICSCOMPONENT_H
