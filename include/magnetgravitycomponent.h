#ifndef MAGNETGRAVITYCOMPONENT_H
#define MAGNETGRAVITYCOMPONENT_H

#include "circlehitboxcomponent.h"
#include "gamebuttoncomponent.h"

class MagnetGravityComponent : public Component
{
public:
    MagnetGravityComponent(float radius, float force = 5, QString requiredButtons = "");
    const static QString HITBOX_NAME;

    void update() override;
    void init() override;

    float getForce() const;
    float getRotation() const;

private:
    QVector<QString> requiredButtons;
    float force = 5;
    float rotation = 0;
    float radius = 0;
};

#endif // MAGNETGRAVITYCOMPONENT_H
