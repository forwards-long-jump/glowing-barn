#ifndef PLAYERSTATE_H
#define PLAYERSTATE_H

#include "game.h"
#include "physicscomponent.h"

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
    PlayerState() {}
    virtual ~PlayerState() {}

    virtual void handleInput(PlayerInputComponent* playerInputComponent) = 0;
    bool handleHorizontalMovement(PlayerInputComponent* playerInputComponent);
    virtual void setHeadingRight(bool headingRight_);
    bool checkFalling(PlayerInputComponent*) const;
    bool checkOnGround(PlayerInputComponent*) const;
    bool checkNoSpeed(PlayerInputComponent*) const;

    virtual void enter(PlayerInputComponent* playerInputComponent) const = 0;

    static StandingState standing;
    static RunningState running;
    static SkiddingState skidding;
    static JumpingState jumping;
    static FallingState falling;
    static ZippingState zipping;

protected:
    static bool headingRight;
};


class RunningState : public PlayerState
{
public:
    RunningState()
        :PlayerState() {}

    void handleInput(PlayerInputComponent* playerInputComponent) override;
    void setHeadingRight(bool headingRight_) override;

    void enter(PlayerInputComponent *playerInputComponent) const override;
};


class SkiddingState : public PlayerState
{
public:
    SkiddingState()
        :PlayerState() {}

    void handleInput(PlayerInputComponent* playerInputComponent) override;
    void setHeadingRight(bool headingRight_) override;

    void enter(PlayerInputComponent *playerInputComponent) const override;
};


class StandingState : public PlayerState
{
public:
    StandingState()
        :PlayerState() {}

    void handleInput(PlayerInputComponent* playerInputComponent) override;
    void setHeadingRight(bool headingRight_) override;

    void enter(PlayerInputComponent *playerInputComponent) const override;
};


class JumpingState : public PlayerState
{
public:
    JumpingState()
        :PlayerState() {}

    void handleInput(PlayerInputComponent* playerInputComponent) override;
    void setHeadingRight(bool headingRight_) override;

    void enter(PlayerInputComponent* playerInputComponent) const override;
};


class FallingState : public PlayerState
{
public:
    FallingState()
        :PlayerState() {}

    void handleInput(PlayerInputComponent *playerInputComponent) override;
    void setHeadingRight(bool headingRight_) override;

    void enter(PlayerInputComponent *playerInputComponent) const override;
};


class ZippingState : public PlayerState
{
public:
    ZippingState()
        :PlayerState() {}

    void handleInput(PlayerInputComponent* playerInputComponent) override;
    void setHeadingRight(bool headingRight_) override;

    void enter(PlayerInputComponent *playerInputComponent) const override;
};

#include <playerinputcomponent.h>

#endif // PLAYERSTATE_H
