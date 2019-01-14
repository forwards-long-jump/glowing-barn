#ifndef INTERACTIVECOMPONENT_H
#define INTERACTIVECOMPONENT_H

#include "hitboxreactorcomponent.h"
#include "interactivereactorcomponent.h"
#include "debugcomponent.h"
#include "input.h"

//belongs to an interactible objet
class InteractiveComponent : public HitboxReactorComponent
{
public:
    InteractiveComponent(Input::Key key_, QString name_ = "InteractiveComponent", QString targetHitboxName = "InteractiveHitboxComponent", QString requiredButtons = "");

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
