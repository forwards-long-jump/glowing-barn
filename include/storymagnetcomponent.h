#ifndef STORYMAGNETCOMPONENT_H
#define STORYMAGNETCOMPONENT_H

#include "gamebuttoncomponent.h"
#include "interactivecomponent.h"
#include "physicscomponent.h"
#include "gamescene.h"
#include "sounds.h"

/**
 * Unique component for the magnet in the prologue of the game.
 *
 * @authors Alexandre Bianchi, Pierre Bürki, Loïck Jeanneret
 */

class StoryMagnetComponent : public HitboxReactorComponent
{
public:
    StoryMagnetComponent(QString requiredButtons_, QString targetMap_);

    void update() override;
    void init() override;

    void onIntersect(HitboxComponent *hb) override;

private:
    QVector<QString> requiredButtons;

    bool alreadyActivated = false;

    QString targetMap;
};

#endif // STORYMAGNETCOMPONENT_H
