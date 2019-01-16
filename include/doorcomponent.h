#ifndef DOORCOMPONENT_H
#define DOORCOMPONENT_H

#include "interactivereactorcomponent.h"
#include "squarehitboxcomponent.h"
#include "gamescene.h"

class DoorComponent : public InteractiveReactorComponent
{
public:
    DoorComponent(QString targetMap, QString targetDoor, QString requiredButtons_ = "", bool isFinalDoor_ = false, Input::Key key_ = Input::INTERACT, QString name_ = "InteractiveComponent");

    //void update() override {}
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
