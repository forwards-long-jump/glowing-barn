#ifndef COLLISIONCOMPONENT_H
#define COLLISIONCOMPONENT_H

#include "component.h"
#include <QList>
#include <QMap>

class HitboxComponent : public Component
{
public:
    HitboxComponent(QString name_ = "HitboxComponent");

    void update() override {}
    virtual bool intersects(HitboxComponent* hitbox) const = 0;

    QPointF getCenter() const;

    void setOffset(const QPointF& offset_);
    void setOffset(float dx, float dy);
    QPointF& getOffset();

    static QList<HitboxComponent*> getInstancesOf(QString name);
    static void removeAll();

protected:
    QPointF offset;

    static QMap<QString,QList<HitboxComponent*>> instances;
};

#endif // COLLISIONCOMPONENT_H
