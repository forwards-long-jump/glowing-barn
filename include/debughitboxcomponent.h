#ifndef DEBUGHITBOXCOMPONENT_H
#define DEBUGHITBOXCOMPONENT_H

#include "graphicscomponent.h"
#include "squarehitboxcomponent.h"

class DebugHitboxComponent : public GraphicsComponent
{
public:
    DebugHitboxComponent(const QColor& color = QColor(0, 255, 0, 127), const QString& name = "DebugHitboxComponent");

    void render(QPainter* painter) override;
    void update() override;
private:
    QColor color;
};

#endif // DEBUGHITBOXCOMPONENT_H
