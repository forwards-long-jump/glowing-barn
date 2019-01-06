#include "soundbuttonreactorcomponent.h"

SoundButtonReactorComponent::SoundButtonReactorComponent(QString startSound_, QString endSound_, QString idleSound_, QString activeSound_,
                                                         QString requiredButtons_, QString name) : Component(name)
{
    startSound = startSound_;
    endSound = endSound_;
    idleSound = idleSound_;
    activeSound = activeSound_;

    requiredButtons = GameButtonComponent::getButtonVectorFromString(requiredButtons_);
}

void SoundButtonReactorComponent::update()
{
    if(GameButtonComponent::areButtonsPressed(requiredButtons))
    {
        switch(currentState)
        {
        case SoundButtonReactorComponent::IDLE:
        case SoundButtonReactorComponent::END:
            currentState = START;
            break;
        case SoundButtonReactorComponent::START:
            Sounds::playSound(startSound);
            currentState = ACTIVE;
            break;
        case SoundButtonReactorComponent::ACTIVE:
            // TODO: Loop active sound or something
            break;
        }
    }
    else
    {
        switch(currentState)
        {
        case SoundButtonReactorComponent::IDLE:
            // TODO: Loop idle sound or something
            break;
        case SoundButtonReactorComponent::START:
        case SoundButtonReactorComponent::ACTIVE:
            currentState = END;
            break;
        case SoundButtonReactorComponent::END:
            Sounds::playSound(endSound);
            currentState = IDLE;
            break;
        }
    }
}
