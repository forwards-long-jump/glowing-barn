#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H

#include <QPainter>

#include "component.h"

/**
 * Abstract component which gives a graphical appearance to its entity
 *
 * @authors Alexandre Bianchi, Pierre Bürki, Loïck Jeanneret
 */

class GraphicsComponent : public Component
{
public:
    GraphicsComponent(const QString& name = "GraphicsComponent");

    virtual void render(QPainter* painter) = 0;
};

#endif // GRAPHICSCOMPONENT_H
