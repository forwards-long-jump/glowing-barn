#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H

#include "component.h"
#include "interactivecomponent.h"

#include <QTime>

class PlayerState;

class PlayerInputComponent : public Component
{
public:
    PlayerInputComponent(QString name_ = "PlayerInputComponent")
        :Component(name_) {}
    virtual ~PlayerInputComponent() {}

    void update() override;
    void init() override;

    PlayerState* getState() const;
    void setState(PlayerState* _state);

    void onDisable() override;

private:
    bool releasedKeyAfterTogglingMagnet;
    PlayerState* state;

    InteractiveComponent interactiveHitbox;
};

#include "playerstate.h"

#endif // INPUTCOMPONENT_H
