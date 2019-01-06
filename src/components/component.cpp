#include "component.h"

Component::Component(const QString& name) : name(name) {}

Component::~Component() {}

void Component::setParent(Entity* parent)
{
    this->parent = parent;
}

Entity* Component::getParent() const
{
    return parent;
}

QString Component::getName() const
{
    return name;
}

void Component::init() {}

void Component::onEnable() {}

void Component::onDisable() {}
