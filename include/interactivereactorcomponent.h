#ifndef INTERACTIVECOMPONENT_H
#define INTERACTIVECOMPONENT_H

#include "hitboxreactorcomponent.h"
#include "interactivecomponent.h"
#include "debugcomponent.h"
#include "input.h"

/**
 * Asks the player for an input on intersection, and acts appropriately when the input is provided
 *
 * @authors Alexandre Bianchi, Pierre Bürki, Loïck Jeanneret
 */

class InteractiveReactorComponent : public HitboxReactorComponent
{
public:
    InteractiveReactorComponent(Input::Key key_, QString name_ = "InteractiveComponent", QString targetHitboxName = InteractiveComponent::HITBOX_NAME, QString requiredButtons = "");

    void update() override;
    void init() override;
    void onIntersect(HitboxComponent* hb) override;

    virtual void showPrompt() const;
    virtual void action(Entity* target) = 0;

protected:
    Input::Key key;
    bool readyToInteract;
    bool removePromptOnNextTick;

    QVector<QString> requiredButtons;

    Entity* commandPrompt;
};

#endif // INTERACTIVECOMPONENT_H
