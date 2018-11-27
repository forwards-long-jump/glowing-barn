#ifndef RECTANGLECOMPONENT_H
#define RECTANGLECOMPONENT_H

#include "include/graphicscomponent.h"

class RectangleComponent : public GraphicsComponent
{
public:
    RectangleComponent();

    void render(QPainter* painter) override;
    void update() override;
};

#endif // RECTANGLECOMPONENT_H
