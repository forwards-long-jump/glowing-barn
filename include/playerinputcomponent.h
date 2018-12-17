#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H

#include "component.h"
#include "playerstate.h"

class PlayerInputComponent : public Component
{
public:
    PlayerInputComponent(QString name_ = "PlayerInputComponent")
        :Component(name_) {}
    virtual ~PlayerInputComponent(){}

    void update() override;
    void init() override;

    PlayerState* getState() const;
    void setState(PlayerState* _state);

private:
    bool releasedKeyAfterTogglingMagnet;
    PlayerState* state;
};

#endif // INPUTCOMPONENT_H
