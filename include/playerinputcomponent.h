#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H

#include "component.h"
#include "playerstate.h"
#include "interactivehitboxcomponent.h"

class PlayerInputComponent : public Component
{
public:
    PlayerInputComponent(QString name_ = "PlayerInputComponent")
        :Component(name_) {jumpLeniencyStart.start();}
    virtual ~PlayerInputComponent() {}

    void update() override;
    void init() override;

    PlayerState* getState() const;
    void setState(PlayerState* _state);

    void resetJumpLeniency() {jumpLeniencyStart.restart();}
    bool isJumpLenient() const {return jumpLeniencyStart.elapsed() < jumpLeniencyInMSec;}

private:
    bool releasedKeyAfterTogglingMagnet;
    PlayerState* state;

    InteractiveHitboxComponent interactiveHitbox;

    QTime jumpLeniencyStart;
    const int jumpLeniencyInMSec = 100;
};

#endif // INPUTCOMPONENT_H
