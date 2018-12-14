#include "include/debugcomponent.h"

DebugComponent::DebugComponent(QString name_, QString str, QColor c)
    :GraphicsComponent(name_)
{
    debugText = str;
    color = c;
}

DebugComponent::DebugComponent(QString str, QColor c)
    : GraphicsComponent("DebugComponent")
{
    debugText = str;
    color = c;
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
    Entity *e = new Entity(this->getEntity(), 1000, 50);
    e->addComponent(new DebugTextComponent("DebugTextComponent", debugText));
}
