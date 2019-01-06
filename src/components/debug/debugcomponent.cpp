#include "debugcomponent.h"

DebugComponent::DebugComponent(const QColor &color, bool hasHitboxComponent, bool hasTextComponent, const QString &debugText, const QString &name) :
    GraphicsComponent(name),
    color(color), hasHitboxComponent(hasHitboxComponent), hasTextComponent(hasTextComponent), debugText(debugText)
{

}

void DebugComponent::setColor(const QColor &color)
{
    this->color = color;
}

void DebugComponent::setDebugText(const QString &text)
{
    if(hasTextComponent) {
        static_cast<DebugTextComponent*>(childDebugEntity->getComponent("DebugTextComponent"))->setText(text);
    }
}

void DebugComponent::render(QPainter* painter)
{
    painter->fillRect(0, 0, parent->getSize().width(), parent->getSize().height(), color);
}

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

void DebugComponent::update() {}
