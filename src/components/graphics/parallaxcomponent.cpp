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
    anchorPos = getParent()->pos();
    float averageXYCoeff = (coeff.x() + coeff.y()) / 2;
    if(averageXYCoeff > 0) {
        getParent()->setZValue(-(10 + averageXYCoeff));
    }
    else {
        getParent()->setZValue(10 - averageXYCoeff);
    }
}

void ParallaxComponent::setAnchor(QPointF p)
{
    anchorPos = p;
}

void ParallaxComponent::update()
{
    GameScene* gameScene = dynamic_cast<GameScene*>(getParent()->scene());
    QPointF cameraPos = gameScene->getCamera()->getPosition();
    QRectF cameraRect = gameScene->getCamera()->getBoundingRect();
    cameraPos.setX(qMax(cameraPos.x(), cameraRect.x()));
    cameraPos.setY(qMax(cameraPos.y(), cameraRect.y()));

    getParent()->setPos(anchorPos.x() + cameraPos.x() * coeff.x(),
                        anchorPos.y() + cameraPos.y() * coeff.y());
}

