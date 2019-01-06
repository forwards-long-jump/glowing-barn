#include "imagecomponent.h"

ImageComponent::ImageComponent(const QString resourcePath, const QString name) : GraphicsComponent(name)
{
    image = QPixmap(resourcePath);
}

void ImageComponent::render(QPainter* painter)
{
    if(mirrored) {
        painter->translate(image.width(), 0);
        painter->scale(-1, 1);
    }

    if(rotation != 0)
    {
        painter->translate(parent->getSize().width() / 2, parent->getSize().height() / 2);
        painter->rotate(rotation);

        painter->drawPixmap(-parent->getSize().width() / 2, - parent->getSize().height() / 2, parent->getSize().width(), parent->getSize().height(), image);

        painter->translate(-parent->getSize().width() / 2, -parent->getSize().height() / 2);
        painter->rotate(-rotation);
    }
    else
    {
        painter->drawPixmap(0, 0, parent->getSize().width(), parent->getSize().height(), image);
    }


    if(mirrored) {
        painter->scale(-1, 1);
        painter->translate(-image.width(), 0);
    }
}

void ImageComponent::setMirrored(bool value)
{
    mirrored = value;
}

void ImageComponent::setRotation(int value)
{
    rotation = value;
}
