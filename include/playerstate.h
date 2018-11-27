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
    PlayerState(){}

    virtual void handleInput(PlayerInputComponent* playerInputComponent, Game* game) = 0;
    virtual void update(PlayerInputComponent* playerInputComponent, Game* game) = 0;

    void init() {timer = dx = dy = 0;}

    static StandingState standing;
    static RunningState running;
    static JumpingState jumping;
    static ZippingState zipping;

protected:
    int dx;
    int dy;

    int timer;

    const int maxDx = 10;
    const int maxDy = 10;
};

class RunningState : public PlayerState
{
public:
    RunningState(){}

    void handleInput(PlayerInputComponent* playerInputComponent, Game* game);
    void update(PlayerInputComponent* playerInputComponent, Game* game);
};

class StandingState : public PlayerState
{
public:
    StandingState(){}

    void handleInput(PlayerInputComponent* playerInputComponent, Game* game);
    void update(PlayerInputComponent* playerInputComponent, Game* game);
};

class JumpingState : public PlayerState
{
public:
    JumpingState(){}

    void handleInput(PlayerInputComponent* playerInputComponent, Game* game);
    void update(PlayerInputComponent* playerInputComponent, Game* game);

private:
    const int timeToMaxHeight = 60;
    const int maxHeight = 100;
};

class ZippingState : public PlayerState
{
public:
    ZippingState(){}

    void handleInput(PlayerInputComponent* playerInputComponent, Game* game);
    void update(PlayerInputComponent* playerInputComponent, Game* game);
};

#include <playerinputcomponent.h>

#endif // PLAYERSTATE_H
