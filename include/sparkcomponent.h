#ifndef SPARKCOMPONENT_H
#define SPARKCOMPONENT_H

#include <QtMath>
#include <QRandomGenerator>

#include "hitboxreactorcomponent.h"
#include "circlehitboxcomponent.h"
#include "animationcomponent.h"

/**
 * Makes its entity follow the player when he is too close, and wiggles randomly around its position
 *
 * @authors Alexandre Bianchi, Pierre Bürki, Loïck Jeanneret
 */

class SparkComponent : public HitboxReactorComponent
{
public:
    SparkComponent(float radius = 50, float speed = 100, QString additionalHitboxName = "", QString name = "SparkComponent");

    void init() override;
    void onIntersect(HitboxComponent* hitboxComponent) override;
    void onEnable() override;
    void update() override;

    const static QString HITBOX_REACTOR_NAME;

private:
    bool playerInSight = false;
    float speed;
    float radius = 50;
    QString additionalHitboxName = "";

    int pauseDurationInTicks = 10;
    int ticksUntilMove;

    QPointF actualPosition;
    QPointF errorComponent;
    float errorRadius = 7;
};

#endif // SPARKCOMPONENT_H
