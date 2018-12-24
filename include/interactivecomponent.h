#ifndef INTERACTIVECOMPONENT_H
#define INTERACTIVECOMPONENT_H

#include "hitboxreactorcomponent.h"
#include "interactivehitboxcomponent.h"
#include "debugcomponent.h"
#include "input.h"

//belongs to an interactible objet
class InteractiveComponent : public HitboxReactorComponent
{
public:
    InteractiveComponent(Input::Key key_, QString name_ = "InteractiveComponent");

    void update() override;
    void init() override;
    void onIntersect(HitboxComponent* hb) override;

    void showPrompt() const;
    virtual void action(Entity* target) const = 0;

protected:
    Input::Key key;
    bool readyToInteract;
    bool removePromptOnNextTick;

    Entity* commandPrompt;
};

#endif // INTERACTIVECOMPONENT_H
