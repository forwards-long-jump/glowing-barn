#ifndef INTERACTIVEHITBOXCOMPONENT_H
#define INTERACTIVEHITBOXCOMPONENT_H

#include "squarehitboxcomponent.h"
#include "input.h"

/**
 * Attached to the player, allows for interaction with InteractiveReactorComponents
 *
 * @authors Alexandre Bianchi, Pierre Bürki, Loïck Jeanneret
 */

class InteractiveComponent : public SquareHitboxComponent
{
public:
    InteractiveComponent(QString name_ = HITBOX_NAME);
    const static QString HITBOX_NAME;

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
