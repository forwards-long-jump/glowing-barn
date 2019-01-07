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
