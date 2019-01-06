#include "genericrendercomponent.h"

void GenericRenderComponent::update()
{
    tick++;
}

void GenericRenderComponent::render(QPainter* painter)
{
    functionToRender(painter, parent, tick);
}

void GenericRenderComponent::circleMagnetHitbox(QPainter* p, Entity* e, int tick)
{
    int diameter = e->getSize().width();

    p->setPen(QColor(58, 68, 102, 50));
    p->setBrush(QColor(90, 105, 136, 50));
    p->drawEllipse(0, 0, diameter, diameter);
}
