#include "textcomponent.h"

/**
 * @brief TextComponent::TextComponent
 * @param text
 * @param buttons
 * @param fontSize
 * @param name
 */
TextComponent::TextComponent(const QString &text, QString buttons, int fontSize, QString name) :
    GraphicsComponent(name),
    fontSize(fontSize),
    text(text)
{
    requiredButtons = GameButtonComponent::getButtonVectorFromString(buttons);
}

/**
 * @brief TextComponent::update
 */
void TextComponent::update()
{

}

/**
 * @brief TextComponent::render
 * @param painter
 */
void TextComponent::render(QPainter *painter)
{

    if(currentBackgroundOpacity > 0)
    {
        painter->setPen(QColor(0, 0, 0, qMax(0, currentBackgroundOpacity - BORDER_OPACITY_OFFSET)));
        painter->setBrush(QColor(0, 0, 0, currentBackgroundOpacity));
        painter->drawRect(parent->boundingRect());

        painter->setFont(QFont("Arial", fontSize));
        painter->setPen(QColor(255, 255, 255, (static_cast<float>(currentBackgroundOpacity) / MAX_BACKGROUND_OPACITY) * 255));
        painter->drawText(QRectF(0, 0, getParent()->getSize().width(), getParent()->getSize().height()), text, QTextOption(Qt::AlignCenter));
    }

    if(requiredButtons.length() == 0 || GameButtonComponent::areButtonsPressed(requiredButtons))
    {
        if(currentBackgroundOpacity < MAX_BACKGROUND_OPACITY) currentBackgroundOpacity += 5;
    }
    else
    {
        if(currentBackgroundOpacity > 1) currentBackgroundOpacity -= 5;
        else currentBackgroundOpacity = 0;
    }
}
