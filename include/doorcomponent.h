#ifndef DOORCOMPONENT_H
#define DOORCOMPONENT_H

#include "interactivereactorcomponent.h"
#include "interactivecomponent.h"
#include "squarehitboxcomponent.h"
#include "gamescene.h"

/**
 * Gives its entity the properties to act as a door
 *
 * @authors Alexandre Bianchi, Pierre Bürki, Loïck Jeanneret
 */

class DoorComponent : public InteractiveReactorComponent
{
public:
    DoorComponent(QString targetMap, QString targetDoor, QString requiredButtons_ = "", bool isFinalDoor_ = false, Input::Key key_ = Input::INTERACT, QString name_ = "InteractiveComponent");

    void init() override;
    void action(Entity* target) override;
    void update() override;

private:
    QString targetMap;
    QString targetDoor;
    bool enteringDoor = false;

    bool isFinalDoor;
};

#endif // DOORCOMPONENT_H
