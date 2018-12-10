#ifndef ZIPPERMAGNET_H
#define ZIPPERMAGNET_H

#include <QRectF>
#include <QSizeF>
#include <QString>
#include "component.h"

class ZipperMagnetComponent : public Component
{
public:
    const QString HITBOX_NAME = "ZipperMagnetHitbox";
    enum DIRECTION { LEFT, RIGHT, UP, DOWN };
    ZipperMagnetComponent(DIRECTION direction, QSizeF hitboxSize, float speed = 5);
    float getSpeed() const;
    DIRECTION getDirection() const;

    QRectF DEBUGRectangle;
    void update() override;

private:
    float speed;
    DIRECTION direction;
};

#endif // ZIPPERMAGNET_H
