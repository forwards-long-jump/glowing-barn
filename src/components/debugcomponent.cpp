#include "include/debugcomponent.h"

DebugComponent::DebugComponent(const QColor &color_, bool hasHitboxComponent_, bool hasTextComponent_, const QString &debugText_, const QString &name_) : GraphicsComponent(name_)
{
    color = color_;
    hasHitboxComponent = hasHitboxComponent_;
    hasTextComponent = hasTextComponent_;
    debugText = debugText_;
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
        Entity *e = new Entity(this->getEntity(), 1920, 1080);
        if(hasTextComponent)
        {
            e->addComponent(new DebugTextComponent("DebugTextComponent", debugText));
        }
        if(hasHitboxComponent)
        {
            e->addComponent(new DebugHitboxComponent);
        }
    }
}
