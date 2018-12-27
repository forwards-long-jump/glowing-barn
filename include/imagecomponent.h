#ifndef IMAGECOMPONENT_H
#define IMAGECOMPONENT_H

#include "graphicscomponent.h"

class ImageComponent : public GraphicsComponent
{
public:
    ImageComponent(const QString resourceName, const QString name = "ImageComponent");

    void render(QPainter* painter) override;
    void update() override {};

private:
    QPixmap image;
};

#endif // IMAGECOMPONENT_H
