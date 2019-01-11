#ifndef GENERICRENDERCOMPONENT_H
#define GENERICRENDERCOMPONENT_H

#include "graphicscomponent.h"
#include "magnetgravitycomponent.h"
#include <qmath.h>


class GenericRenderComponent : public GraphicsComponent
{
public:
    GenericRenderComponent(void(*functionToRender)(QPainter* p, Entity* e, int tick)) : functionToRender(functionToRender) {}

    void update() override;
    void render(QPainter* painter) override;

    static void circleMagnetHitbox(QPainter* p, Entity* e, int tick);
    static void magnetEnabledEffect(QPainter* p, Entity* e, int tick);

private:
    void (*functionToRender)(QPainter* p, Entity* e, int tick);
    int tick = 0;
};

#endif // GENERICRENDERCOMPONENT_H
