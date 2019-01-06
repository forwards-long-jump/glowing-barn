#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H

#include <QPainter>

#include "component.h"

class GraphicsComponent : public Component
{
public:
    GraphicsComponent(const QString& name = "GraphicsComponent");

    virtual void render(QPainter* painter) = 0;
};

#endif // GRAPHICSCOMPONENT_H
