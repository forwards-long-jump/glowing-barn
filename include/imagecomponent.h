#ifndef IMAGECOMPONENT_H
#define IMAGECOMPONENT_H

#include "graphicscomponent.h"
#include "gamebuttoncomponent.h"

/**
 * Draws an image on screen
 *
 * @authors Alexandre Bianchi, Pierre Bürki, Loïck Jeanneret
 */

class ImageComponent : public GraphicsComponent
{
public:
    ImageComponent(const QString resourcePath, const QString name = "ImageComponent", const QString &requiredButtons = "");

    void render(QPainter* painter) override;
    void update() override {}

    void setMirrored(bool value);

    void setRotation(int value);

private:
    QPixmap image;
    QVector<QString> requiredButtons;
    bool mirrored = false;
    int rotation = 0;
};

#endif // IMAGECOMPONENT_H
