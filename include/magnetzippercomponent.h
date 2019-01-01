#ifndef ZIPPERMAGNET_H
#define ZIPPERMAGNET_H

#include <QRectF>
#include <QSizeF>
#include <QString>

#include "squarehitboxcomponent.h"
#include "gamebuttoncomponent.h"

class MagnetZipperComponent : public Component
{
public:
    enum DIRECTION { LEFT, RIGHT, UP, DOWN };
    const static QString HITBOX_NAME;

    MagnetZipperComponent(DIRECTION direction, QSizeF hitboxSize, float speed = 5, QString requiredButtons = "");

    float getSpeed() const;
    DIRECTION getDirection() const;

    void update() override;
    void init() override;

private:
    float speed;
    QSizeF hitboxSize;
    QVector<QString> requiredButtons;
    DIRECTION direction;
};

#endif // ZIPPERMAGNET_H
