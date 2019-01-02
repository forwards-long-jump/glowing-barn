#include "animationcomponent.h"

AnimationComponent::AnimationComponent(const QString resourcePath, float frameWidth_, QVector<QPair<QString, QVector<float> > > animationProperties_, QString buttons,
                                       const QString name) : GraphicsComponent(name)
{
    image = QPixmap(resourcePath);
    frameWidth = frameWidth_;

    requiredButtons = GameButtonComponent::getButtonVectorFromString(buttons);
    currentAnimationVectorIndex = 0;
    currentAnimationStartingIndex = 0;
    currentFrameIndex = 0;
    ticksBeforeNextFrame = 0;
    animationProperties = animationProperties_;
    loopingDisabled = false;
    mirrored = false;
    currentButtonAnimationState = ButtonAnimationState::IDLE;
}

void AnimationComponent::addAnimationToVector(QString animationName, int frameCount, int framesDuration, QVector<QPair<QString, QVector<float> > > &animationVector)
{
    QPair<QString, QVector<float>> animation;
    animation.first = animationName;
    QVector<float> framesDurations;
    framesDurations.fill(framesDuration, frameCount);
    animation.second = framesDurations;
    animationVector.append(animation);
}

void AnimationComponent::setCurrentAnimation(QString animation)
{
    ticksBeforeNextFrame = 0;
    currentAnimationStartingIndex = 0;
    currentFrameIndex = 0;

    // Find which animation to play and track its starting index
    for(int i = 0; i < animationProperties.length(); ++i)
    {
        if(animationProperties[i].first != animation)
        {
            currentAnimationStartingIndex += animationProperties[i].second.size();
        }
        else
        {
            currentAnimationVectorIndex = i;
            break;
        }
    }

    loopingDisabled = false;
}

void AnimationComponent::disableLooping()
{
    loopingDisabled = true;
}

void AnimationComponent::setMirrored(bool mirrored_)
{
    mirrored = mirrored_;
}

void AnimationComponent::setButtons(QString buttons)
{
    requiredButtons = GameButtonComponent::getButtonVectorFromString(buttons);
}

void AnimationComponent::render(QPainter *painter)
{
    int entityWidth = entity->getSize().width();
    int entityHeight = entity->getSize().height();

    if(mirrored) {
        painter->translate(entityWidth, 0);
        painter->scale(-1, 1);
    }

    painter->drawPixmap(0, 0, entityWidth, entityHeight,
                        image,
                        frameWidth * (currentFrameIndex + currentAnimationStartingIndex), 0, frameWidth, image.height());

    if(mirrored) {
        painter->scale(-1, 1);
        painter->translate(-entityWidth, 0);
    }
}

void AnimationComponent::update()
{
    bool reactToButtons = false;
    // If the animation reacts to buttons, set the current animation depending on the state
    if(requiredButtons.length() > 0)
    {
        reactToButtons = true;
        if(GameButtonComponent::areButtonsPressed(requiredButtons))
        {
            // All required buttons pressed, move to active animation
            switch(currentButtonAnimationState)
            {
                case ButtonAnimationState::IDLE:
                case ButtonAnimationState::END:
                    currentButtonAnimationState = ButtonAnimationState::START;
                    setCurrentAnimation("start");
                    break;
            }
        }
        else
        {
            // Some required buttons aren't pressed, move to idle animation
            switch(currentButtonAnimationState)
            {
            case ButtonAnimationState::START:
            case ButtonAnimationState::ACTIVE:
                currentButtonAnimationState = ButtonAnimationState::END;
                setCurrentAnimation("end");
                break;
            }
        }
    }

    ticksBeforeNextFrame--;
    // Next animation frame
    if(ticksBeforeNextFrame < 0)
    {
        currentFrameIndex++;
        // Restart to first frame
        if(currentFrameIndex >= animationProperties[currentAnimationVectorIndex].second.size())
        {
            if(loopingDisabled)
            {
                currentFrameIndex--;
            }
            else
            {
                currentFrameIndex = 0;
            }
        }
        ticksBeforeNextFrame = animationProperties[currentAnimationVectorIndex].second.at(currentFrameIndex);

        if(reactToButtons && currentFrameIndex == 0)
        {
            switch(currentButtonAnimationState)
            {
            case ButtonAnimationState::END:
                currentButtonAnimationState = ButtonAnimationState::IDLE;
                setCurrentAnimation("idle");
                break;
            case ButtonAnimationState::START:
                currentButtonAnimationState = ButtonAnimationState::ACTIVE;
                setCurrentAnimation("active");
                break;
            }
        }
    }
}
