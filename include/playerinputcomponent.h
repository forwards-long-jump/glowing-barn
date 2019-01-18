#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H

#include "component.h"
#include "interactivecomponent.h"
#include "scene.h"

#include <QTime>

class PlayerState;

/**
 * Handles input, attached only to the playable character
 *
 * @authors Alexandre Bianchi, Pierre Bürki, Loïck Jeanneret
 */

class PlayerInputComponent : public Component
{
public:
    PlayerInputComponent(QString name_ = "PlayerInputComponent");
    virtual ~PlayerInputComponent() {}

    void update() override;
    void init() override;

    PlayerState* getState() const;
    void setState(PlayerState* _state);

    void onDisable() override;

private:
    void handleMagnetActivation();

    bool releasedKeyAfterTogglingMagnet;
    PlayerState* state;

    InteractiveComponent interactiveHitbox;
};

#include "playerstate.h"

#endif // INPUTCOMPONENT_H
