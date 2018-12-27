#include "imagecomponent.h"

ImageComponent::ImageComponent(const QString resourceName, const QString name) : GraphicsComponent(name)
{
    image = QPixmap("://" + resourceName);
}

void ImageComponent::render(QPainter *painter)
{
    painter->drawPixmap(0, 0, entity->getSize().width(), entity->getSize().height(), image);
}
