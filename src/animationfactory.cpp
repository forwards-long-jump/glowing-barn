#include "animationfactory.h"

AnimationComponent* AnimationFactory::getAnimationComponent(QString animationName)
{
    QVector<QPair<QString, QVector<float>>> animations;

    if(animationName == "player")
    {
        AnimationComponent::addAnimationToVector("running", 8, 2, animations);
        AnimationComponent::addAnimationToVector("standing", 2, 15, animations);
        AnimationComponent::addAnimationToVector("skidding", 1, 1, animations);
        AnimationComponent::addAnimationToVector("jumping", 1, 1, animations);
        AnimationComponent::addAnimationToVector("zipping", 3, 10, animations);
        AnimationComponent::addAnimationToVector("falling", 1, 1, animations);
        AnimationComponent::addAnimationToVector("door", 9, 3, animations);
        AnimationComponent::addAnimationToVector("death", 6, 1, animations);
        return new AnimationComponent(":/entities/player.png", 16, animations);
    }
    else if(animationName == "playerStory")
    {
        AnimationComponent::addAnimationToVector("running", 8, 2, animations);
        AnimationComponent::addAnimationToVector("standing", 2, 15, animations);
        AnimationComponent::addAnimationToVector("skidding", 1, 1, animations);
        AnimationComponent::addAnimationToVector("jumping", 1, 1, animations);
        AnimationComponent::addAnimationToVector("zipping", 3, 10, animations);
        AnimationComponent::addAnimationToVector("falling", 1, 1, animations);
        AnimationComponent::addAnimationToVector("door", 9, 3, animations);
        AnimationComponent::addAnimationToVector("death", 6, 1, animations);
        return new AnimationComponent(":/entities/playerStory.png", 16, animations);
    }
    else if(animationName == "lever")
    {
        AnimationComponent::addAnimationToVector("start", 3, 1, animations);
        AnimationComponent::addAnimationToVector("end", 3, 1, animations);
        AnimationComponent::addAnimationToVector("idle", 1, 1, animations);
        AnimationComponent::addAnimationToVector("active", 1, 1, animations);
        return new AnimationComponent(":/entities/lever.png", 16, animations);
    }
    else if(animationName == "plate")
    {
        AnimationComponent::addAnimationToVector("start", 3, 1, animations);
        AnimationComponent::addAnimationToVector("end", 3, 1, animations);
        AnimationComponent::addAnimationToVector("idle", 1, 1, animations);
        AnimationComponent::addAnimationToVector("active", 1, 1, animations);
        return new AnimationComponent(":/entities/plate.png", 16, animations);
    }
    else if(animationName == "magnet-wave")
    {
        AnimationComponent::addAnimationToVector("active", 8, 3, animations);
        AnimationComponent::addAnimationToVector("end", 2, 4, animations);
        AnimationComponent::addAnimationToVector("start", 2, 4, animations);
        AnimationComponent::addAnimationToVector("idle", 1, 2, animations);
        return new AnimationComponent(":/entities/magnet-wave.png", 16, animations);
    }
    else if(animationName == "spark")
    {
        AnimationComponent::addAnimationToVector("idle", 1, 1, animations);
        AnimationComponent::addAnimationToVector("move", 1, 1, animations);
        return new AnimationComponent(":/entities/spark.png", 17, animations);
    }
    else if(animationName == "door")
    {
        AnimationComponent::addAnimationToVector("idle", 1, 1, animations);
        AnimationComponent::addAnimationToVector("start", 3, 1, animations);
        AnimationComponent::addAnimationToVector("active", 1, 1, animations);
        AnimationComponent::addAnimationToVector("end", 3, 0, animations);
        return new AnimationComponent(":/entities/door.png", 16, animations);
    }
    else if(animationName == "keyboard")
    {
        AnimationComponent::addAnimationToVector("down", 2, 10, animations);
        AnimationComponent::addAnimationToVector("left", 2, 10, animations);
        AnimationComponent::addAnimationToVector("right", 2, 10, animations);
        AnimationComponent::addAnimationToVector("up", 2, 10, animations);
        return new AnimationComponent(":/interface/arrowkeys.png", 16, animations);
    }
    else if(animationName == "magnetJumper")
    {
        AnimationComponent::addAnimationToVector("active", 1, 1, animations);
        AnimationComponent::addAnimationToVector("idle", 1, 1, animations);
        AnimationComponent::addAnimationToVector("end", 2, 1, animations);
        AnimationComponent::addAnimationToVector("start", 2, 1, animations);
        return new AnimationComponent(":/entities/magnet-jumper.png", 16, animations);
    }
    else if(animationName == "magnetZipper")
    {
            AnimationComponent::addAnimationToVector("active", 1, 1, animations);
            AnimationComponent::addAnimationToVector("idle", 1, 1, animations);
            AnimationComponent::addAnimationToVector("end", 2, 1, animations);
            AnimationComponent::addAnimationToVector("start", 2, 1, animations);
            return new AnimationComponent(":/entities/magnet-zipper.png", 16, animations);
    }
    else if(animationName == "magnetGravity")
    {
        AnimationComponent::addAnimationToVector("active", 1, 1, animations);
        AnimationComponent::addAnimationToVector("idle", 1, 1, animations);
        AnimationComponent::addAnimationToVector("end", 2, 1, animations);
        AnimationComponent::addAnimationToVector("start", 2, 1, animations);
        return new AnimationComponent(":/entities/magnet-gravity.png", 16, animations);
    }
    else if(animationName == "boxContainer")
    {
            AnimationComponent::addAnimationToVector("start", 3, 1, animations);
            AnimationComponent::addAnimationToVector("end", 3, 1, animations);
            AnimationComponent::addAnimationToVector("idle", 1, 1, animations);
            AnimationComponent::addAnimationToVector("active", 1, 1, animations);
            return new AnimationComponent(":/entities/box-container.png", 26, animations);
    }
    // Missing / invalid animation
    assert(false);
    return nullptr;
}

AnimationFactory::AnimationFactory() {}
