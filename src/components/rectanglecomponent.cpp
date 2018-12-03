#include "include/rectanglecomponent.h"

RectangleComponent::RectangleComponent()
{

}

void RectangleComponent::render(QPainter *painter)
{
    painter->fillRect(entity->boundingRect(), Qt::blue);
}

void RectangleComponent::update()
{

}
