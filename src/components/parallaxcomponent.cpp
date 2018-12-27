#include "parallaxcomponent.h"
/**
 * @brief ParallaxComponent::ParallaxComponent
 * @param coeff_ The x/y "depth" of the entity, negative= background, positive  = foreground
 * @param name
 */
ParallaxComponent::ParallaxComponent(QPointF coeff_, QString name)  : Component(name)
{
    coeff = coeff_;
}

void ParallaxComponent::init()
{
    anchorPos = getEntity()->pos();
    float averageXYCoeff = (coeff.x() + coeff.y()) / 2;
    getEntity()->setZValue((averageXYCoeff < 0 ? 10 : -10) + averageXYCoeff);
}

void ParallaxComponent::setAnchor(QPointF p)
{
    anchorPos = p;
}

void ParallaxComponent::update()
{
    GameScene* gameScene = dynamic_cast<GameScene*>(getEntity()->scene());
    QPointF cameraPos = gameScene->getCamera()->getPosition();
    getEntity()->setPos(anchorPos.x() + cameraPos.x() * coeff.x(), anchorPos.y() + cameraPos.y() * coeff.y());
}

