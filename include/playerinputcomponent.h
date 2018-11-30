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

    PlayerState* getState() const;
    void setState(PlayerState* _state);

private:
    PlayerState* state;
};

#endif // INPUTCOMPONENT_H
