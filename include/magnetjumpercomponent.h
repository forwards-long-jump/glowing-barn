#ifndef MAGNETJUMPERCOMPONENT_H
#define MAGNETJUMPERCOMPONENT_H

#include "component.h"
#include "squarehitboxcomponent.h"
#include "gamebuttoncomponent.h"

class MagnetJumperComponent : public Component
{
public:
    MagnetJumperComponent(float force = 5, float rotation = 0, QString requiredButtons = "");
    const static QString HITBOX_NAME;

    void update() override;
    void init() override;

    float getForce() const;
    float getRotation() const;

private:
    QVector<QString> requiredButtons;
    float force = 5;
    float rotation = 0;
};

#endif // MAGNETJUMPERCOMPONENT_H
