#ifndef STORYACTIVATIONCOMPONENT_H
#define STORYACTIVATIONCOMPONENT_H

#include "gamebuttoncomponent.h"
#include "animationcomponent.h"

class StoryActivationComponent : public GameButtonComponent
{
public:
    StoryActivationComponent(QString buttonName);

    void update() override;
    void showPrompt() const override {}
    void action(Entity *target) override;
};

#endif // STORYACTIVATIONCOMPONENT_H
