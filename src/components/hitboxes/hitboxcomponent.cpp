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

void HitboxComponent::setOffset(const QPointF& offset_)
{
    offset = offset_;
}

void HitboxComponent::setOffset(float dx, float dy)
{
    offset = QPointF(dx, dy);
}

QPointF HitboxComponent::getOffset() const
{
    return offset;
}

QList<HitboxComponent*> HitboxComponent::getInstancesOf(QString name)
{
    return instances[name];
}

void HitboxComponent::onDisable()
{
    instances[this->name].removeOne(this);
}

void HitboxComponent::onEnable()
{
    instances[this->name].append(this);
}

HitboxComponent::~HitboxComponent()
{
    instances[this->name].removeOne(this);
}


void HitboxComponent::removeAll()
{
    instances.clear();
}

