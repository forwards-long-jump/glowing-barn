#ifndef INTERACTIVEHITBOXCOMPONENT_H
#define INTERACTIVEHITBOXCOMPONENT_H

#include "squarehitboxcomponent.h"
#include "input.h"

//belongs to a player
class InteractiveReactorComponent : public SquareHitboxComponent
{
public:
    InteractiveReactorComponent(QString name_ = "InteractiveHitboxComponent");

    void update() override;

    void askKey(Input::Key key);

    Input::Key getAskedKey() const {return askedKey;}
    bool isActive() const {return isKeyActive;}
    void setActive(bool active_) {isKeyActive = active_;}

private:
    Input::Key askedKey;
    bool isKeyActive;
};

#endif // INTERACTIVEHITBOXCOMPONENT_H
