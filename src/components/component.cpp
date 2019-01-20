#include "component.h"

/**
 * @brief Component::Component
 * @param name
 */
Component::Component(const QString& name)
    : name(name)
{

}

/**
 * @brief Component::~Component
 */
Component::~Component() {}

/**
 * @brief Component::setParent
 * @param parent
 */
void Component::setParent(Entity* parent)
{
    this->parent = parent;
}

/**
 * @brief Component::getParent
 * @return
 */
Entity* Component::getParent() const
{
    return parent;
}

/**
 * @brief Component::getName
 * @return
 */
QString Component::getName() const
{
    return name;
}

/**
 * @brief Component::init
 */
void Component::init() {}

/**
 * @brief Component::onEnable
 */
void Component::onEnable() {}

/**
 * @brief Component::onDisable
 */
void Component::onDisable() {}
