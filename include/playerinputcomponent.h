#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H

#include "component.h"
#include "playerstate.h"

class PlayerInputComponent : public Component
{
public:
    PlayerInputComponent();

    void update() override;
    void handleInput();
    void setState(PlayerState* _state) {state = _state; state->init();}

    StandingState standing;
    RunningState running;
    JumpingState jumping;
    ZippingState zipping;

private:
    PlayerState* state;
};

#endif // INPUTCOMPONENT_H
