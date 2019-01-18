#ifndef GENERICRENDERCOMPONENT_H
#define GENERICRENDERCOMPONENT_H

#include "graphicscomponent.h"
#include "magnetgravitycomponent.h"
#include <qmath.h>

/**
 * This component takes a renderer function allowing to render any custom graphic needed by an entity
 *
 * @authors Alexandre Bianchi, Pierre Bürki, Loïck Jeanneret
 */

class GenericRenderComponent : public GraphicsComponent
{
public:
    GenericRenderComponent(void(*functionToRender)(QPainter* p, Entity* e, int tick));

    void update() override;
    void render(QPainter* painter) override;

    static void circleMagnetHitbox(QPainter* p, Entity* e, int tick);
    static void magnetEnabledEffect(QPainter* p, Entity* e, int tick);

private:
    void (*functionToRender)(QPainter* p, Entity* e, int tick);
    int tick = 0;
};

#endif // GENERICRENDERCOMPONENT_H
