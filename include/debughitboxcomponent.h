#ifndef DEBUGHITBOXCOMPONENT_H
#define DEBUGHITBOXCOMPONENT_H

#include "graphicscomponent.h"
#include "hitboxcomponent.h"

class DebugHitboxComponent : public GraphicsComponent
{
public:
    DebugHitboxComponent (QString name = "DebugHitboxComponent", QColor color = QColor(0, 255, 0, 127));

    void render(QPainter* painter) override;
    void update() override;
private:
    QColor color;
};

#endif // DEBUGHITBOXCOMPONENT_H
