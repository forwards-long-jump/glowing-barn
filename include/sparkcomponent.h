#ifndef SPARKCOMPONENT_H
#define SPARKCOMPONENT_H

#include "hitboxreactorcomponent.h"
#include "circlehitboxcomponent.h"
#include "animationcomponent.h"

class SparkComponent : public HitboxReactorComponent
{
public:
    SparkComponent(float radius = 50, QString name = "SparkComponent");

    void init() override;
    void onIntersect(HitboxComponent* hitboxComponent) override;
    void onEnable() override;
    void update() override;

    const static QString HITBOX_REACTOR_NAME;

private:
    bool playerInSight = false;
    float radius;
};

#endif // SPARKCOMPONENT_H
