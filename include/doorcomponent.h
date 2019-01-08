#ifndef DOORCOMPONENT_H
#define DOORCOMPONENT_H

#include "interactivecomponent.h"
#include "squarehitboxcomponent.h"
#include "gamescene.h"

class DoorComponent : public InteractiveComponent
{
public:
    DoorComponent(QString targetMap, QString targetDoor, QString requiredButtons_ = "", Input::Key key_ = Input::INTERACT, QString name_ = "InteractiveComponent");

    //void update() override {}
    void init() override;
    void action(Entity* target) override;
private:
    QString targetMap;
    QString targetDoor;
};

#endif // DOORCOMPONENT_H
