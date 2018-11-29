#ifndef PLAYERSTATE_H
#define PLAYERSTATE_H

#include "game.h"

class PlayerInputComponent;
class StandingState;
class RunningState;
class JumpingState;
class ZippingState;

class PlayerState
{
public:
    PlayerState(float ddx_ = 0, float ddy_ = 0)
        :ddx(ddx_), ddy(ddy_) {}
    virtual ~PlayerState() {}

    virtual void handleInput(PlayerInputComponent* playerInputComponent, Game* game) = 0;

    virtual void enter(PlayerInputComponent* playerInputComponent) {}

    static StandingState standing;
    static RunningState running;
    static JumpingState jumping;
    static ZippingState zipping;

protected:
    float ddx;
    float ddy;
};

class RunningState : public PlayerState
{
public:
    RunningState()
        :PlayerState(1, 0) {}

    void handleInput(PlayerInputComponent* playerInputComponent, Game* game);
};

class StandingState : public PlayerState
{
public:
    StandingState()
        :PlayerState(0, 0) {}

    void handleInput(PlayerInputComponent* playerInputComponent, Game* game);
};

class JumpingState : public PlayerState
{
public:
    JumpingState()
        :PlayerState(1, 0) {}

    void handleInput(PlayerInputComponent* playerInputComponent, Game* game);

    void enter(PlayerInputComponent* playerInputComponent) override;

private:
    const float jumpSpeed = -30;
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
