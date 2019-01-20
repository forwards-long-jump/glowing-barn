#include "genericrendercomponent.h"

/**
 * @brief GenericRenderComponent::GenericRenderComponent
 * @param functionToRender lambda rendering function
 */
GenericRenderComponent::GenericRenderComponent(void (*functionToRender)(QPainter *, Entity *, int))
    : functionToRender(functionToRender)
{

}

/**
 * @brief GenericRenderComponent::update
 */
void GenericRenderComponent::update()
{
    tick++;
}

/**
 * @brief GenericRenderComponent::render
 * @param painter
 */
void GenericRenderComponent::render(QPainter* painter)
{
    functionToRender(painter, parent, tick);
}

/**
 * @brief GenericRenderComponent::circleMagnetHitbox
 * Rendering function for gravity magnets
 * @param painter
 * @param entity
 * @param tick
 */
void GenericRenderComponent::circleMagnetHitbox(QPainter* p, Entity* e, int tick)
{
    int diameter = e->getSize().width();

    MagnetGravityComponent* mgc = static_cast<MagnetGravityComponent*>(e->getParent()->getComponent("MagnetGravityComponent"));


    p->setOpacity(1 - qMin(mgc->getDisabledTime() / 20.0, 1.0));
    float speed = (mgc->getForce() - 0.25) / 99.75f + 2;
    int activeRadius = static_cast<int>(tick * speed) % diameter / 2;

    p->setBrush(Qt::transparent);
    p->setPen(QColor(255, 255, 255, 127 - (activeRadius / (diameter / 2.0f)) * 127));

    if(mgc->getForce() > 0)
    {
        p->drawEllipse(QPointF(diameter / 2, diameter / 2), activeRadius, activeRadius);
    }
    else
    {
        p->drawEllipse(QPointF(diameter / 2, diameter / 2), -activeRadius + diameter / 2, -activeRadius +  diameter / 2);
    }

    p->setPen(QColor(255, 255, 255, 127));
    p->setBrush(QColor(255, 255, 255, 50));
    p->drawEllipse(0, 0, diameter, diameter);

}

/**
 * @brief GenericRenderComponent::magnetEnabledEffect
 * Rendering function for jumper magnets
 * @param painter
 * @param entity
 * @param tick
 */
void GenericRenderComponent::magnetEnabledEffect(QPainter *p, Entity *e, int tick)
{
    QBrush redBrush();
    QBrush blueBrush(QColor(0, 145, 228));

    int entityHeight = e->getSize().height();
    int entityWidth = e->getSize().width();

    for(int i = 0; i < 3; ++i)
    {
        float y = entityHeight - (1 + i) * static_cast<int>((tick * 0.6)) % entityHeight;
        float x = entityWidth * 0.5 * (1 + qSin(i + tick * 0.1));
        p->fillRect(x, y, 2, 2, QColor(248, 0, 67, (y / entityHeight) * 255));
    }

    for(int i = 0; i < 3; ++i)
    {
        float y = entityHeight - (1 + i) * static_cast<int>((tick * 0.55)) % entityHeight;
        float x = entityWidth * 0.5 * (1 + qSin(1 + i + tick * 0.1));
        p->fillRect(x, y, 2, 2, QColor(0, 145, 228, (y / entityHeight) * 255));
    }
}
