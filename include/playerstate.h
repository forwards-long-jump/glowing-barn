#ifndef PLAYERSTATE_H
#define PLAYERSTATE_H

#include "game.h"
#include "physicscomponent.h"
#include "animationcomponent.h"

class PlayerInputComponent;

class StandingState;
class RunningState;
class SkiddingState;
class JumpingState;
class FallingState;
class ZippingState;
class DeadState;

/**
 * Abstract class which handles the input
 *
 * @authors Alexandre Bianchi, Pierre Bürki, Loïck Jeanneret
 */

class PlayerState
{
public:
    PlayerState() {}
    virtual ~PlayerState() {}

    virtual void handleInput(PlayerInputComponent* playerInputComponent) = 0;
    bool handleHorizontalMovement(PlayerInputComponent* playerInputComponent);
    virtual void setHeadingRight(bool headingRight_, PlayerInputComponent* playerInputComponent);
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
    static DeadState dying;

protected:
    static bool headingRight;
    static int ticksSinceEntering;
};

/**
 * Handles input for a running player
 *
 * @authors Alexandre Bianchi, Pierre Bürki, Loïck Jeanneret
 */

class RunningState : public PlayerState
{
public:
    RunningState()
        : PlayerState() {}

    void handleInput(PlayerInputComponent* playerInputComponent) override;

    void enter(PlayerInputComponent* playerInputComponent) const override;
};

/**
 * Handles input for a skidding player
 *
 * @authors Alexandre Bianchi, Pierre Bürki, Loïck Jeanneret
 */

class SkiddingState : public PlayerState
{
public:
    SkiddingState()
        : PlayerState() {}

    void handleInput(PlayerInputComponent* playerInputComponent) override;

    void enter(PlayerInputComponent* playerInputComponent) const override;
};

/**
 * Handles input for a standing player
 *
 * @authors Alexandre Bianchi, Pierre Bürki, Loïck Jeanneret
 */

class StandingState : public PlayerState
{
public:
    StandingState()
        : PlayerState() {}

    void handleInput(PlayerInputComponent* playerInputComponent) override;

    void enter(PlayerInputComponent* playerInputComponent) const override;
};

/**
 * Handles input for a jumping player
 *
 * @authors Alexandre Bianchi, Pierre Bürki, Loïck Jeanneret
 */

class JumpingState : public PlayerState
{
public:
    JumpingState()
        : PlayerState() {}

    void handleInput(PlayerInputComponent* playerInputComponent) override;

    void enter(PlayerInputComponent* playerInputComponent) const override;

public:
    const int nbTicksJumping = 7;
};

/**
 * Handles input for a falling player
 *
 * @authors Alexandre Bianchi, Pierre Bürki, Loïck Jeanneret
 */

class FallingState : public PlayerState
{
public:
    FallingState()
        :PlayerState() {}

    void handleInput(PlayerInputComponent* playerInputComponent) override;

    void enter(PlayerInputComponent* playerInputComponent) const override;

    void setLenient(bool lenient);

private:
    const int jumpLeniency = 5;
    bool canBeLenient = false;
};

/**
 * Handles input for a dead player
 *
 * @authors Alexandre Bianchi, Pierre Bürki, Loïck Jeanneret
 */

class DeadState : public PlayerState
{
public:
    DeadState()
        :PlayerState() {}

    void handleInput(PlayerInputComponent* playerInputComponent) override {}
    void setHeadingRight(bool headingRight_, PlayerInputComponent* playerInputComponent) override {}

    void enter(PlayerInputComponent* playerInputComponent) const override;
};

/**
 * Handles input for a player zipping to a magnet
 *
 * @authors Alexandre Bianchi, Pierre Bürki, Loïck Jeanneret
 */

class ZippingState : public PlayerState
{
public:
    ZippingState()
        :PlayerState() {}

    void handleInput(PlayerInputComponent* playerInputComponent) override;

    void enter(PlayerInputComponent* playerInputComponent) const override;
};

#include "playerinputcomponent.h"

#endif // PLAYERSTATE_H
