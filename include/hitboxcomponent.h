#ifndef COLLISIONCOMPONENT_H
#define COLLISIONCOMPONENT_H

#include "component.h"
#include <QList>
#include <QMap>

/**
 * Gives its entity an area of the scene to trigger certain behaviors
 *
 * @authors Alexandre Bianchi, Pierre Bürki, Loïck Jeanneret
 */

class HitboxComponent : public Component
{
public:
    HitboxComponent(QString name_ = "HitboxComponent");

    void update() override {}
    virtual bool intersects(HitboxComponent* hitbox) const = 0;

    virtual QPointF getCenter() const = 0;

    void setOffset(const QPointF& offset_);
    void setOffset(float dx, float dy);
    QPointF getOffset() const;

    void onEnable() override;
    void onDisable() override;
    ~HitboxComponent();

    static QList<HitboxComponent*> getInstancesOf(QString name);
    static void removeAll();

protected:
    QPointF offset;

    static QMap<QString,QList<HitboxComponent*>> instances;
};

#endif // COLLISIONCOMPONENT_H
