#ifndef ZIPPERMAGNET_H
#define ZIPPERMAGNET_H

#include <QRectF>
#include <QSizeF>
#include <QString>

#include "squarehitboxcomponent.h"
#include "animationcomponent.h"
#include "animationfactory.h"
#include "imagecomponent.h"

/**
 * Captures and pulls any entity set to react to it with a "tractor beam"
 *
 * @authors Alexandre Bianchi, Pierre Bürki, Loïck Jeanneret
 */

class MagnetZipperComponent : public Component
{
public:
    enum DIRECTION { LEFT, RIGHT, UP, DOWN };
    const static QString HITBOX_NAME;

    MagnetZipperComponent(DIRECTION direction, QSizeF hitboxSize, float speed = 5, QString requiredButtons_ = "", bool noAnimations = false);

    float getSpeed() const;
    DIRECTION getDirection() const;

    void update() override;
    void init() override;

private:
    const int WAVE_ANIMATION_SIZE = 16;
    void addAnimations();
    int rotation = 0;
    float speed = 5;
    QSizeF hitboxSize;
    QVector<QString> requiredButtons;
    bool noAnimations = false;
    DIRECTION direction;
};

#include "gamebuttoncomponent.h"

#endif // ZIPPERMAGNET_H
