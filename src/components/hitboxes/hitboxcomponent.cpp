#include "hitboxcomponent.h"

QMap<QString, QList<HitboxComponent*>> HitboxComponent::instances;

/**
 * @brief HitboxComponent::HitboxComponent
 * @param name_
 */
HitboxComponent::HitboxComponent(QString name_)
    : Component(name_)
{
    if (! instances.contains(name_))
    {
        instances.insert(name_, QList<HitboxComponent*>());
    }
    instances[name_].append(this);
}

/**
 * @brief HitboxComponent::setOffset
 * @param offset_
 */
void HitboxComponent::setOffset(const QPointF& offset_)
{
    offset = offset_;
}

/**
 * @brief HitboxComponent::setOffset
 * @param dx
 * @param dy
 */
void HitboxComponent::setOffset(float dx, float dy)
{
    offset = QPointF(dx, dy);
}

/**
 * @brief HitboxComponent::getOffset
 * @return
 */
QPointF HitboxComponent::getOffset() const
{
    return offset;
}

/**
 * @brief HitboxComponent::getInstancesOf
 * Returns all instances of hitboxes with the specified name
 * @param name
 * @return
 */
QList<HitboxComponent*> HitboxComponent::getInstancesOf(QString name)
{
    return instances[name];
}

/**
 * @brief HitboxComponent::onDisable
 */
void HitboxComponent::onDisable()
{
    instances[this->name].removeOne(this);
}

/**
 * @brief HitboxComponent::onEnable
 */
void HitboxComponent::onEnable()
{
    instances[this->name].append(this);
}

/**
 * @brief HitboxComponent::~HitboxComponent
 */
HitboxComponent::~HitboxComponent()
{
    instances[this->name].removeOne(this);
}

/**
 * @brief HitboxComponent::removeAll
 */
void HitboxComponent::removeAll()
{
    instances.clear();
}

