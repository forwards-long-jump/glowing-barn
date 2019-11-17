#include "animationcomponent.h"

/**
 * @brief AnimationComponent::AnimationComponent
 * @param resourcePath
 * @param frameWidth
 * @param animationProperties
 * @param buttons
 * @param name
 */
AnimationComponent::AnimationComponent(const QString resourcePath, float frameWidth_, QVector<QPair<QString, QVector<float> > > animationProperties_, QString buttons,
                                       const QString name)
    : GraphicsComponent(name)
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

/**
 * @brief AnimationComponent::addAnimationToVector
 * @param animationName
 * @param frameCount
 * @param framesDuration
 * @param animationVector
 */
void AnimationComponent::addAnimationToVector(QString animationName, int frameCount, int framesDuration, QVector<QPair<QString, QVector<float> > > &animationVector)
{
    QPair<QString, QVector<float>> animation;
    animation.first = animationName;
    QVector<float> framesDurations;
    framesDurations.fill(framesDuration, frameCount);
    animation.second = framesDurations;
    animationVector.append(animation);
}

/**
 * @brief AnimationComponent::setCurrentAnimation
 * @param animation
 */
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

/**
 * @brief AnimationComponent::disableLooping
 */
void AnimationComponent::disableLooping()
{
    loopingDisabled = true;
}

/**
 * @brief AnimationComponent::setMirrored
 * @param mirrored
 */
void AnimationComponent::setMirrored(bool mirrored_)
{
    mirrored = mirrored_;
}

/**
 * @brief AnimationComponent::setButtons
 * @param buttons
 */
void AnimationComponent::setButtons(QString buttons)
{
    setButtons(GameButtonComponent::getButtonVectorFromString(buttons));
}

/**
 * @brief AnimationComponent::setButtons
 * @param buttons
 */
void AnimationComponent::setButtons(QVector<QString> buttons)
{
    requiredButtons = buttons;
    if(requiredButtons.length() > 0)
    {
        setCurrentAnimation("idle");
    }
}

/**
 * @brief AnimationComponent::render
 * @param painter
 */
void AnimationComponent::render(QPainter* painter)
{
    int entityWidth = parent->getSize().width();
    int entityHeight = parent->getSize().height();

    if(mirrored)
    {
        painter->translate(entityWidth, 0);
        painter->scale(-1, 1);
    }

    if(mirroredY)
    {
        painter->translate(0, entityHeight);
        painter->scale(1, -1);
    }

    if(rotation != 0)
    {
        painter->translate(entityWidth / 2, entityHeight / 2);
        painter->rotate(rotation);

       if(tiled) {
            painter->drawTiledPixmap(-entityWidth / 2, -entityHeight / 2, entityWidth, entityHeight,
                                image.copy(frameWidth * (currentFrameIndex + currentAnimationStartingIndex), 0, frameWidth, image.height()));
        }
        else {
            painter->drawPixmap(-entityWidth / 2, -entityHeight / 2, entityWidth, entityHeight,
                                image,
                                frameWidth * (currentFrameIndex + currentAnimationStartingIndex), 0, frameWidth, image.height());
        }
        painter->translate(-entityWidth / 2, -entityHeight / 2);
        painter->rotate(-rotation);
    }
    else
    {
        if(tiled) {
            painter->drawTiledPixmap(0, 0, entityWidth, entityHeight,
                            image.copy(frameWidth * (currentFrameIndex + currentAnimationStartingIndex), 0, frameWidth, image.height()));
        }
        else {
            painter->drawPixmap(0, 0, entityWidth, entityHeight,
                            image,
                            frameWidth * (currentFrameIndex + currentAnimationStartingIndex), 0, frameWidth, image.height());
        }
    }

    if(mirroredY)
    {
        painter->scale(1, -1);
        painter->translate(0, -entityHeight);
    }

    if(mirrored)
    {
        painter->scale(-1, 1);
        painter->translate(-entityWidth, 0);
    }

}

/**
 * @brief AnimationComponent::update
 */
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

    ticksBeforeNextFrame -= speedMultiplier;
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

/**
 * @brief AnimationComponent::setSpeedMultiplier
 * @param value
 */
void AnimationComponent::setSpeedMultiplier(int value)
{
    speedMultiplier = value;
}

/**
 * @brief AnimationComponent::getRotation
 * @return
 */
int AnimationComponent::getRotation() const
{
    return rotation;
}

/**
 * @brief AnimationComponent::getMirrored
 * @return
 */
bool AnimationComponent::getMirrored() const
{
    return mirrored;
}

bool AnimationComponent::getTiled() const
{
    return tiled;
}

void AnimationComponent::setTiled(bool value)
{
    tiled = value;
}

bool AnimationComponent::getMirroredY() const
{
    return mirroredY;
}

void AnimationComponent::setMirroredY(bool value)
{
    mirroredY = value;
}

void AnimationComponent::setImage(const QPixmap &value)
{
    image = value;
}

/**
 * @brief AnimationComponent::setRotation
 * @param value
 */
void AnimationComponent::setRotation(int value)
{
    rotation = value;
}
