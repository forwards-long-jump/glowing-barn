#ifndef PLAYERSTATE_H
#define PLAYERSTATE_H

#include "game.h"
#include "physicscomponent.h"

const float groundFriction = 0.75;
const float airFriction = 0.8;

class PlayerInputComponent;

class StandingState;
class RunningState;
class SkiddingState;
class JumpingState;
class FallingState;
class ZippingState;

class PlayerState
{
public:
    PlayerState(float friction_)
        :friction(friction_) {}
    virtual ~PlayerState() {}

    virtual void handleInput(PlayerInputComponent* playerInputComponent) = 0;
    bool handleHorizontalMovement(PlayerInputComponent* playerInputComponent);
    bool checkFalling(PlayerInputComponent*) const;
    bool checkOnGround(PlayerInputComponent*) const;
    bool checkNoSpeed(PlayerInputComponent*) const;

    virtual void enter(PlayerInputComponent* playerInputComponent) const;

    static StandingState standing;
    static RunningState running;
    static SkiddingState skidding;
    static JumpingState jumping;
    static FallingState falling;
    static ZippingState zipping;

protected:
    float friction;

    static bool headingRight;
};


class RunningState : public PlayerState
{
public:
    RunningState()
        :PlayerState(groundFriction) {}

    void handleInput(PlayerInputComponent* playerInputComponent) override;

    void enter(PlayerInputComponent *playerInputComponent) const override;
};


class SkiddingState : public PlayerState
{
public:
    SkiddingState()
        :PlayerState(groundFriction) {}

    void handleInput(PlayerInputComponent* playerInputComponent) override;

    void enter(PlayerInputComponent *playerInputComponent) const override;
};


class StandingState : public PlayerState
{
public:
    StandingState()
        :PlayerState(groundFriction) {}

    void handleInput(PlayerInputComponent* playerInputComponent) override;

    void enter(PlayerInputComponent *playerInputComponent) const override;
};


class JumpingState : public PlayerState
{
public:
    JumpingState()
        :PlayerState(airFriction) {}

    void handleInput(PlayerInputComponent* playerInputComponent) override;

    void enter(PlayerInputComponent* playerInputComponent) const override;
};


class FallingState : public PlayerState
{
public:
    FallingState()
        :PlayerState(airFriction) {}

    void handleInput(PlayerInputComponent *playerInputComponent) override;

    void enter(PlayerInputComponent *playerInputComponent) const override;
};


class ZippingState : public PlayerState
{
public:
    ZippingState()
        :PlayerState(airFriction) {}

    void handleInput(PlayerInputComponent* playerInputComponent) override;

    void enter(PlayerInputComponent *playerInputComponent) const override {}
};

#include <playerinputcomponent.h>

#endif // PLAYERSTATE_H
