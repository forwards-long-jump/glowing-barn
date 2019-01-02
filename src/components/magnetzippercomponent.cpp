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
    SquareHitboxComponent *hc = new SquareHitboxComponent(HITBOX_NAME);
    getEntity()->addComponent(hc);

    QPointF entityCenter(getEntity()->getSize().width() / 2, getEntity()->getSize().height() / 2);
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
    int w = hitboxSize.width() / WAVE_ANIMATION_SIZE - 1;

    // Add magnet image
    Entity* magnetImage = new Entity(entity->parentItem(), entity->x(), entity->y(), WAVE_ANIMATION_SIZE, WAVE_ANIMATION_SIZE);
    ImageComponent* ic = new ImageComponent(":/entities/magnet-zipper.png");
    magnetImage->addComponent(ic);

    switch(direction)
    {
    case DIRECTION::RIGHT:
        for(int i = 1; i < w; ++i)
        {
            Entity* e = new Entity(entity->parentItem(), entity->x() + i * WAVE_ANIMATION_SIZE, entity->y(), WAVE_ANIMATION_SIZE, WAVE_ANIMATION_SIZE);
            AnimationComponent* ac = AnimationFactory::getAnimationComponent("magnet-wave");
            ac->setButtons(requiredButtons);
            ac->setMirrored(true);
            e->addComponent(ac);
        }
        break;
    case DIRECTION::LEFT:
        ic->setMirrored(true);
        for(int i = 1; i < w; ++i)
        {
            Entity* e = new Entity(entity->parentItem(), entity->x() - i * WAVE_ANIMATION_SIZE, entity->y(), WAVE_ANIMATION_SIZE, WAVE_ANIMATION_SIZE);
            AnimationComponent* ac = AnimationFactory::getAnimationComponent("magnet-wave");
            ac->setButtons(requiredButtons);
            e->addComponent(ac);
        }
        break;
    case DIRECTION::UP:
        ic->setRotation(-90);
        for(int i = 1; i < w; ++i)
        {
            Entity* e = new Entity(entity->parentItem(), entity->x(), entity->y() - i * WAVE_ANIMATION_SIZE, WAVE_ANIMATION_SIZE, WAVE_ANIMATION_SIZE);
            AnimationComponent* ac = AnimationFactory::getAnimationComponent("magnet-wave");
            ac->setRotation(90);
            ac->setButtons(requiredButtons);
            e->addComponent(ac);
        }
        break;
    case DIRECTION::DOWN:
        ic->setRotation(90);
        for(int i = 1; i < w; ++i)
        {
            Entity* e = new Entity(entity->parentItem(), entity->x(), entity->y() + i * WAVE_ANIMATION_SIZE, WAVE_ANIMATION_SIZE, WAVE_ANIMATION_SIZE);
            AnimationComponent* ac = AnimationFactory::getAnimationComponent("magnet-wave");
            ac->setRotation(-90);
            ac->setButtons(requiredButtons);
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
            getEntity()->enableComponent(HITBOX_NAME);
        }
        else
        {
            getEntity()->disableComponent(HITBOX_NAME);
        }
    }
}

// TODO: Remove hitbox component on detach
