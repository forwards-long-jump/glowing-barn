#include "debughitboxcomponent.h"


DebugHitboxComponent::DebugHitboxComponent (QString name_, QColor c) : GraphicsComponent(name_)
{
    color = c;
}

void DebugHitboxComponent::render(QPainter *painter)
{
    Entity* e = nullptr;
    if(this->getEntity()->parentItem()) {
        e = static_cast<Entity*>(this->getEntity()->parentItem());
    }
    else {
        e = entity;
    }

    // Component list
    QMap<QString, Component*>* dhc = e->getComponents();
    QMap<QString, Component*>::const_iterator i = dhc->constBegin();

    painter->setPen(Qt::black);
    while (i != dhc->constEnd())
    {
        HitboxComponent* hc = dynamic_cast<HitboxComponent*>(i.value());
        if(hc)
        {
             painter->fillRect(hc->getOffset().x(), hc->getOffset().y(), hc->getSize().width(), hc->getSize().height(), color);
             painter->drawText(hc->getOffset().x() + 2, hc->getOffset().y() + 12, QString("%0").arg(i.key()));
        }
        ++i;
    }
}

void DebugHitboxComponent::update()
{

}
