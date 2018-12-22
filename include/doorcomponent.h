#ifndef DOORCOMPONENT_H
#define DOORCOMPONENT_H

#include "interactivecomponent.h"

class DoorComponent : public InteractiveComponent
{
public:
    DoorComponent(Input::Key key_ = Input::INTERACT, QString name_ = "InteractiveComponent")
        :InteractiveComponent(key_, name_) {}

    //void update() override {}
    void action(Entity *target) const override;
};

#endif // DOORCOMPONENT_H
