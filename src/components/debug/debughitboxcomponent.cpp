#include "debughitboxcomponent.h"


DebugHitboxComponent::DebugHitboxComponent(const QColor &c, const QString &name) : GraphicsComponent(name)
{
    color = c;
}

void DebugHitboxComponent::render(QPainter* painter)
{
    Entity* e = nullptr;
    if(this->getParent()->parentItem()) {
        e = static_cast<Entity*>(this->getParent()->parentItem());
    }
    else {
        e = parent;
    }

    // Component list
    QMap<QString, Component*>* dhc = e->getComponents();
    QMap<QString, Component*>::const_iterator i = dhc->constBegin();

    painter->setPen(Qt::black);
    while (i != dhc->constEnd())
    {
        SquareHitboxComponent* hc = dynamic_cast<SquareHitboxComponent*>(i.value());
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
