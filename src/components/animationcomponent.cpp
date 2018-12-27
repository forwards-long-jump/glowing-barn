#include "animationcomponent.h"

AnimationComponent::AnimationComponent(const QString resourceName, float frameWidth_, QVector<QPair<QString, QVector<float> > > animationProperties_,
                                       const QString name) : GraphicsComponent(name)
{
    image = QPixmap("://" + resourceName);
    frameWidth = frameWidth_;

    currentAnimationVectorIndex = 0;
    currentAnimationStartingIndex = 0;
    currentFrameIndex = 0;
    ticksBeforeNextFrame = 0;
    animationProperties = animationProperties_;
    loopingDisabled = false;
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
    }
}
