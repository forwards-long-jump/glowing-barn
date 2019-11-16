#include "imagecomponent.h"

/**
 * @brief ImageComponent::ImageComponent
 * @param resourcePath
 * @param name
 * @param buttons
 */
ImageComponent::ImageComponent(const QString resourcePath, const QString name, const QString& buttons)
    : GraphicsComponent(name)
{
    requiredButtons = GameButtonComponent::getButtonVectorFromString(buttons);
    image = QPixmap(resourcePath);
}

/**
 * @brief ImageComponent::render
 * @param painter
 */
void ImageComponent::render(QPainter* painter)
{
    if(requiredButtons.length() > 0 && !GameButtonComponent::areButtonsPressed(requiredButtons))
    {
        return;
    }

    if(mirrored) {
        painter->translate(parent->getSize().width(), 0);
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
        painter->translate(-parent->getSize().width(), 0);
    }
}

/**
 * @brief ImageComponent::setMirrored
 * @param mirrored
 */
void ImageComponent::setMirrored(bool value)
{
    mirrored = value;
}

/**
 * @brief ImageComponent::setRotation
 * @param mirrored
 */
void ImageComponent::setRotation(int value)
{
    rotation = value;
}
