#include "debugcomponent.h"

/**
 * @brief DebugComponent::DebugComponent
 *
 * @param color
 * @param hasHitboxComponent
 * @param hasTextComponent
 * @param debugText
 * @param name
 */
DebugComponent::DebugComponent(const QColor &color, bool hasHitboxComponent, bool hasTextComponent, const QString &debugText, const QString &name)
    : GraphicsComponent(name),
    color(color), hasHitboxComponent(hasHitboxComponent), hasTextComponent(hasTextComponent), debugText(debugText)
{

}

/**
 * @brief DebugComponent::setColor
 * @param color
 */
void DebugComponent::setColor(const QColor &color)
{
    this->color = color;
}

/**
 * @brief DebugComponent::setDebugText
 * @param text
 */
void DebugComponent::setDebugText(const QString &text)
{
    if(hasTextComponent) {
        static_cast<DebugTextComponent*>(childDebugEntity->getComponent("DebugTextComponent"))->setText(text);
    }
}

/**
 * @brief DebugComponent::render
 * @param painter
 */
void DebugComponent::render(QPainter* painter)
{
    painter->fillRect(0, 0, parent->getSize().width(), parent->getSize().height(), color);
}

/**
 * @brief DebugComponent::init
 */
void DebugComponent::init()
{
    if(hasTextComponent || hasHitboxComponent) {
        childDebugEntity = new Entity(this->getParent(), QSizeF(DEBUG_ENTITY_WIDTH, DEBUG_ENTITY_HEIGHT));
        if(hasTextComponent)
        {
            childDebugEntity->setZValue(9999);
            parent->setZValue(9999);
            childDebugEntity->addComponent(new DebugTextComponent("DebugTextComponent", debugText));
        }
        if(hasHitboxComponent)
        {
            childDebugEntity->addComponent(new DebugHitboxComponent);
        }
    }
}

/**
 * @brief DebugComponent::update
 */
void DebugComponent::update() {}
