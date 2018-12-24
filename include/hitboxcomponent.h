#ifndef COLLISIONCOMPONENT_H
#define COLLISIONCOMPONENT_H

#include "component.h"
#include <QList>
#include <QMap>

class HitboxComponent : public Component
{
public:
    HitboxComponent(QString name_ = "HitboxComponent");

    void update() override;
    void init() override;

    void setSize(const QSizeF& hitbox_);
    void setSize(float w, float h);
    QSizeF& getSize() {return size;}

    void setOffset(const QPointF& offset_);
    void setOffset(float dx, float dy);
    QPointF& getOffset() {return offset;}

    QRectF getHitbox() const;

    bool intersects(const HitboxComponent* hitbox) const;

    static QList<HitboxComponent*> getInstancesOf(QString name);

protected:
    QPointF offset;
    QSizeF size;

    static QMap<QString,QList<HitboxComponent*>> instances;
};

#endif // COLLISIONCOMPONENT_H
