#include "debughitboxcomponent.h"


DebugHitboxComponent ::DebugHitboxComponent (QString name_, QColor c)
    :GraphicsComponent(name_)
{
    color = c;
}

void DebugHitboxComponent::render(QPainter *painter)
{
    // Component list
    QMap<QString, Component*>* dhc = entity->getComponents();
    QMap<QString, Component*>::const_iterator i = dhc->constBegin();

    painter->setPen(Qt::black);
    while (i != dhc->constEnd())
    {
        HitboxComponent* hc = dynamic_cast<HitboxComponent*>(i.value());
        if(hc)
        {
             painter->fillRect(hc->getOffset().x(), hc->getOffset().y(), hc->getSize().width(), entity->getSize().height(), color);
             painter->drawText(2, 12, QString("%0").arg(i.key()));
        }
        ++i;
    }
}

void DebugHitboxComponent::update()
{

}
