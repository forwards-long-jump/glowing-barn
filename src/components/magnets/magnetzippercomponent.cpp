#include "magnetzippercomponent.h"

/**
 * @brief The name that will be used everywhere to identify the associated HitboxComponent
 */
const QString MagnetZipperComponent::HITBOX_NAME = "MagnetZipperHitbox";

/**
 * @brief ZipperMagnetComponent::ZipperMagnetComponent
 * @param direction
 * @param hitboxSize
 * @param speed
 */
MagnetZipperComponent::MagnetZipperComponent(DIRECTION direction_, QSizeF hitboxSize_, float speed_, QString requiredButtons_) : Component("MagnetZipperComponent")
{
    hitboxSize = hitboxSize_;
    direction = direction_;

    requiredButtons = GameButtonComponent::getButtonVectorFromString(requiredButtons_);

    speed = speed_;
}

/**
 * @brief Create an HitboxComponent, attach it to the current entity and set its size
 */
void MagnetZipperComponent::init()
{
    SquareHitboxComponent* hc = new SquareHitboxComponent(HITBOX_NAME);
    getParent()->addComponent(hc);

    QPointF entityCenter(getParent()->getSize().width() / 2, getParent()->getSize().height() / 2);
    QRectF hitboxRect;

    switch(direction)
    {
    case DIRECTION::RIGHT:
        hitboxRect.setCoords(
                    entityCenter.x(),  entityCenter.y() - hitboxSize.height() / 2,
                    hitboxSize.width(),  entityCenter.y() - hitboxSize.height() / 2 + hitboxSize.height());
        break;
    case DIRECTION::LEFT: {
        hitboxRect.setCoords(
                    entityCenter.x() - hitboxSize.width(),  entityCenter.y() - hitboxSize.height() / 2,
                    entityCenter.x(),  entityCenter.y() - hitboxSize.height() / 2 + hitboxSize.height());
    }
        break;
    case DIRECTION::DOWN:
        hitboxRect.setCoords(
                    entityCenter.y() - hitboxSize.height() / 2, entityCenter.x(),
                    entityCenter.y() - hitboxSize.height() / 2 + hitboxSize.height(), hitboxSize.width());
        break;
    case DIRECTION::UP:
        hitboxRect.setCoords(
                    entityCenter.y() - hitboxSize.height() / 2, entityCenter.x() - hitboxSize.width(),
                    entityCenter.y() - hitboxSize.height() / 2 + hitboxSize.height(), entityCenter.x());
        break;
    }

    hc->setOffset(hitboxRect.x(), hitboxRect.y());
    hc->setSize(hitboxRect.width(), hitboxRect.height());

    addAnimations();
}

void MagnetZipperComponent::addAnimations()
{
    int w = hitboxSize.width() / WAVE_ANIMATION_SIZE + 1;

    // Add magnet image
    Entity* parentAnimation = new Entity(parent->parentItem(), parent->x(), parent->y(), WAVE_ANIMATION_SIZE, WAVE_ANIMATION_SIZE);
    AnimationComponent* zipperAnimation = AnimationFactory::getAnimationComponent("magnetZipper");
    zipperAnimation->setButtons(requiredButtons);
    parentAnimation->addComponent(zipperAnimation);

    switch(direction)
    {
    case DIRECTION::RIGHT:
        for(int i = 1; i < w; ++i)
        {
            Entity* e = new Entity(parent->parentItem(), parent->x() + i * WAVE_ANIMATION_SIZE, parent->y(), WAVE_ANIMATION_SIZE, WAVE_ANIMATION_SIZE);
            AnimationComponent* ac = AnimationFactory::getAnimationComponent("magnet-wave");
            ac->setButtons(requiredButtons);
            ac->setMirrored(true);
            ac->setSpeedMultiplier(speed / 3);
            e->addComponent(ac);
        }
        break;
    case DIRECTION::LEFT:
        zipperAnimation->setMirrored(true);
        for(int i = 1; i < w; ++i)
        {
            Entity* e = new Entity(parent->parentItem(), parent->x() - i * WAVE_ANIMATION_SIZE, parent->y(), WAVE_ANIMATION_SIZE, WAVE_ANIMATION_SIZE);
            AnimationComponent* ac = AnimationFactory::getAnimationComponent("magnet-wave");
            ac->setButtons(requiredButtons);
            ac->setSpeedMultiplier(speed / 3);
            e->addComponent(ac);
        }
        break;
    case DIRECTION::UP:
        zipperAnimation->setRotation(-90);
        for(int i = 1; i < w; ++i)
        {
            Entity* e = new Entity(parent->parentItem(), parent->x(), parent->y() - i * WAVE_ANIMATION_SIZE, WAVE_ANIMATION_SIZE, WAVE_ANIMATION_SIZE);
            AnimationComponent* ac = AnimationFactory::getAnimationComponent("magnet-wave");
            ac->setRotation(90);
            ac->setButtons(requiredButtons);
            ac->setSpeedMultiplier(speed / 3);
            e->addComponent(ac);
        }
        break;
    case DIRECTION::DOWN:
        zipperAnimation->setRotation(90);
        for(int i = 1; i < w; ++i)
        {
            Entity* e = new Entity(parent->parentItem(), parent->x(), parent->y() + i * WAVE_ANIMATION_SIZE, WAVE_ANIMATION_SIZE, WAVE_ANIMATION_SIZE);
            AnimationComponent* ac = AnimationFactory::getAnimationComponent("magnet-wave");
            ac->setRotation(-90);
            ac->setButtons(requiredButtons);
            ac->setSpeedMultiplier(speed / 3);
            e->addComponent(ac);
        }
        break;
    }
}

/**
 * @brief ZipperMagnetComponent::getSpeed
 * @return
 */
float MagnetZipperComponent::getSpeed() const
{
    return speed;
}

/**
 * @brief ZipperMagnetComponent::getDirection
 * @return
 */
MagnetZipperComponent::DIRECTION MagnetZipperComponent::getDirection() const
{
    return direction;
}

void MagnetZipperComponent::update() {
    if(requiredButtons.length() > 0)
    {
        if(GameButtonComponent::areButtonsPressed(requiredButtons))
        {
            getParent()->enableComponent(HITBOX_NAME);
        }
        else
        {
            getParent()->disableComponent(HITBOX_NAME);
        }
    }
}



// TODO: Remove hitbox component on detach
