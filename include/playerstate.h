#ifndef PLAYERSTATE_H
#define PLAYERSTATE_H

#include "game.h"

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
    PlayerState(float xAcceleration_ = 0)
        :xAcceleration(xAcceleration_) {}
    virtual ~PlayerState() {}

    virtual void handleInput(PlayerInputComponent* playerInputComponent, Game* game) = 0;
    bool handleHorizontalMovement(PlayerInputComponent* playerInputComponent, Game* game) const;
    void decelerate(PlayerInputComponent* playerInputComponent, Game* game);

    virtual void enter(PlayerInputComponent* playerInputComponent) {}

    static StandingState standing;
    static RunningState running;
    static SkiddingState skidding;
    static JumpingState jumping;
    static FallingState falling;
    static ZippingState zipping;

protected:
    float xAcceleration;
};

class RunningState : public PlayerState
{
public:
    RunningState()
        :PlayerState(1) {}

    void handleInput(PlayerInputComponent* playerInputComponent, Game* game);
};

class SkiddingState : public PlayerState
{
public:
    SkiddingState()
        :PlayerState(0) {}

    void handleInput(PlayerInputComponent* playerInputComponent, Game* game);
};

class StandingState : public PlayerState
{
public:
    StandingState()
        :PlayerState(0) {}

    void handleInput(PlayerInputComponent* playerInputComponent, Game* game);
};

class JumpingState : public PlayerState
{
public:
    JumpingState()
        :PlayerState(1) {}

    void handleInput(PlayerInputComponent* playerInputComponent, Game* game);

    void enter(PlayerInputComponent* playerInputComponent) override;

private:
    const float jumpSpeed = -30;
};

class FallingState : public PlayerState
{
public:
    FallingState()
        :PlayerState(1) {}

    void handleInput(PlayerInputComponent *playerInputComponent, Game *game);
};

class ZippingState : public PlayerState
{
public:
    ZippingState()
        :PlayerState() {}

    void handleInput(PlayerInputComponent* playerInputComponent, Game* game);
};

#include <playerinputcomponent.h>

#endif // PLAYERSTATE_H
