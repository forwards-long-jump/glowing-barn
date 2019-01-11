#ifndef STORYMAGNETCOMPONENT_H
#define STORYMAGNETCOMPONENT_H

#include "gamebuttoncomponent.h"
#include "physicscomponent.h"
#include "gamescene.h"
#include "sounds.h"

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
