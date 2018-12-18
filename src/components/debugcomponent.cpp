#include "debugcomponent.h"

DebugComponent::DebugComponent(const QColor &color_, bool hasHitboxComponent_, bool hasTextComponent_, const QString &debugText_, const QString &name_) : GraphicsComponent(name_)
{
    color = color_;
    hasHitboxComponent = hasHitboxComponent_;
    hasTextComponent = hasTextComponent_;
    debugText = debugText_;
}

void DebugComponent::setColor(const QColor &color_)
{
    color = color_;
}

void DebugComponent::setDebugText(const QString &text_)
{
    if(hasTextComponent) {
        static_cast<DebugTextComponent*>(childDebugEntity->getComponent("DebugTextComponent"))->setText(text_);
    }
}

void DebugComponent::render(QPainter *painter)
{
    painter->fillRect(0, 0, entity->getSize().width(), entity->getSize().height(), color);
}

void DebugComponent::update()
{

}

void DebugComponent::init()
{
    if(hasTextComponent || hasHitboxComponent) {
        childDebugEntity = new Entity(this->getEntity(), DEBUG_ENTITY_WIDTH, DEBUG_ENTITY_HEIGHT);
        if(hasTextComponent)
        {
            childDebugEntity->setZValue(9999);
            entity->setZValue(9999);
            childDebugEntity->addComponent(new DebugTextComponent("DebugTextComponent", debugText));
        }
        if(hasHitboxComponent)
        {
            childDebugEntity->addComponent(new DebugHitboxComponent);
        }
    }
}
