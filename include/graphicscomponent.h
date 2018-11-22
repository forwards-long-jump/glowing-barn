#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H

#include "include/component.h"
#include <QPainter>

class GraphicsComponent : public Component
{
public:
    GraphicsComponent();

    virtual void render(QPainter* painter) = 0;
};

#endif // GRAPHICSCOMPONENT_H
