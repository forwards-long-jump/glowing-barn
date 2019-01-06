#ifndef ANIMATIONFACTORY_H
#define ANIMATIONFACTORY_H

#include "animationcomponent.h"

class AnimationFactory
{
public:
    // I decided to not use an enum because the map editor doesn't support them
    // and it would mean having to add a convert function and update it for each new animation
    // This could probably be replaced in the future by something that loads animations from a file
    static AnimationComponent* getAnimationComponent(QString animationName);
private:
    AnimationFactory();
};

#endif // ANIMATIONFACTORY_H
