#include "include/hitboxcomponent.h"

QMap<QString, QList<HitboxComponent*>> HitboxComponent::instances;

HitboxComponent::HitboxComponent(QString name_)
    :Component(name_)
{
    if (! instances.contains(name_))
    {
        instances.insert(name_, QList<HitboxComponent*>());
    }
    instances[name_].append(this);
}

QPointF HitboxComponent::getCenter() const
{
    return entity->pos() + offset;
}

void HitboxComponent::setOffset(const QPointF& offset_)
{
    offset = offset_;
}

void HitboxComponent::setOffset(float dx, float dy)
{
    offset = QPointF(dx, dy);
}

QPointF& HitboxComponent::getOffset()
{
    return offset;
}

QList<HitboxComponent*> HitboxComponent::getInstancesOf(QString name)
{
    return instances[name];
}

void HitboxComponent::removeAll()
{
    instances.clear();
}

