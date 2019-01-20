#include "camerasequencecomponent.h"

/**
 * @brief CameraSequenceComponent::CameraSequenceComponent
 * @param buttons Buttons required to be activated
 * @param cameraSpeed
 * @param lockCameraDuration
 * @param lockPlayerInput
 * @param playOnce
 * @param name
 */
CameraSequenceComponent::CameraSequenceComponent(QString buttons, float cameraSpeed, int lockCameraDuration,
                                                 bool lockPlayerInput, bool playOnce, QString name)
    : Component(name), cameraSpeed(cameraSpeed), lockCameraDuration(lockCameraDuration), lockPlayerInput(lockPlayerInput), playOnce(playOnce)
{
    requiredButtons = GameButtonComponent::getButtonVectorFromString(buttons);
}

/**
 * @brief CameraSequenceComponent::update
 */
void CameraSequenceComponent::update()
{
    Camera* c = static_cast<Scene*>(getParent()->scene())->getCamera();

    // Only start a new sequence when the current one ended
    if(GameButtonComponent::areButtonsPressed(requiredButtons) && (!playOnce || !playedOnce) && enabledDurationInTick < 0 && sequenceEnded)
    {
        if(lockPlayerInput)
        {
            static_cast<GameScene*>(getParent()->scene())->getPlayer()->disableComponent("PlayerInputComponent");
        }

        previousSpeed = c->getSpeed();
        previousEntity = c->getEntity();
        c->setSpeed(cameraSpeed);
        c->attachTo(getParent());
        enabledDurationInTick = lockCameraDuration;
        sequenceEnded = false;
        playedOnce = true;
    }
    else
    {
        if(enabledDurationInTick >= 0)
        {
            enabledDurationInTick--;
            if(enabledDurationInTick == 0)
            {
                c->attachTo(previousEntity);
            }
        }
        else
        {
            if(!sequenceEnded)
            {
                if(c->reachedTarget())
                {
                    c->setSpeed(previousSpeed);
                    if(lockPlayerInput)
                    {
                        static_cast<GameScene*>(getParent()->scene())->getPlayer()->enableComponent("PlayerInputComponent");
                    }
                    sequenceEnded = true;
                }
            }
        }
    }
}
