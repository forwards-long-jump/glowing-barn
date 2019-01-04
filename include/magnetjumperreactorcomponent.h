#ifndef MAGNETJUMPERREACTORCOMPONENT_H
#define MAGNETJUMPERREACTORCOMPONENT_H

#include "hitboxreactorcomponent.h"
#include "physicscomponent.h"
#include "magnetjumpercomponent.h"
#include "playerinputcomponent.h"
#include <QtCore/qmath.h>

class MagnetJumperReactorComponent : public HitboxReactorComponent
{
public:
    MagnetJumperReactorComponent(QString name = "MagnetJumperReactorComponent");

    void init() override;
    void onIntersect(HitboxComponent* hitboxComponent) override;
};

#endif // MAGNETJUMPERREACTORCOMPONENT_H
