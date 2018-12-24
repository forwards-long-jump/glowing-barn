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

void HitboxComponent::update()
{

}

void HitboxComponent::init()
{
    setOffset(0, 0);
    setSize(entity->getSize());
}

void HitboxComponent::setSize(const QSizeF &hitbox_)
{
    size = hitbox_;
}

void HitboxComponent::setSize(float w, float h)
{
    setSize(QSizeF(w, h));
}

void HitboxComponent::setOffset(const QPointF &offset_)
{
    offset = offset_;
}

void HitboxComponent::setOffset(float dx, float dy)
{
    setOffset(QPointF(dx, dy));
}

QRectF HitboxComponent::getHitbox() const
{
    return QRectF(entity->pos() + offset, size);
}

bool HitboxComponent::intersects(const HitboxComponent *hitbox) const
{
    return getHitbox().intersects(hitbox->getHitbox());
}

QList<HitboxComponent*> HitboxComponent::getInstancesOf(QString name)
{
    return instances[name];
}

