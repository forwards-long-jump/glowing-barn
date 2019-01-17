#ifndef MAGNETJUMPERCOMPONENT_H
#define MAGNETJUMPERCOMPONENT_H

#include "component.h"
#include "squarehitboxcomponent.h"
#include "gamebuttoncomponent.h"

/**
 * Gives any entity set to react to it upwards momentum on intersection
 *
 * @authors Alexandre Bianchi, Pierre Bürki, Loïck Jeanneret
 */

class MagnetJumperComponent : public Component
{
public:
    MagnetJumperComponent(float force = 5, float rotation = 0, QString requiredButtons = "");
    const static QString HITBOX_NAME;

    void update() override;
    void init() override;

    float getForce() const;
    float getRotation() const;

    bool isDisabled() const;

private:
    QVector<QString> requiredButtons;
    float force = 5;
    float rotation = 0;
    bool disabled = false;
};

#endif // MAGNETJUMPERCOMPONENT_H
