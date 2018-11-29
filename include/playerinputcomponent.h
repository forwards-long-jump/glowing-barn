#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H

#include "component.h"
#include "playerstate.h"

class PlayerInputComponent : public Component
{
public:
    PlayerInputComponent();
    virtual ~PlayerInputComponent(){}

    void update() override;
    void setState(PlayerState* _state) {state = _state; state->enter(this);}

private:
    PlayerState* state;
};

#endif // INPUTCOMPONENT_H
