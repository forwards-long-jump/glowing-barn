#ifndef RECTANGLECOMPONENT_H
#define RECTANGLECOMPONENT_H

#include "graphicscomponent.h"
#include "debugtextcomponent.h"
#include "debughitboxcomponent.h"

class DebugComponent : public GraphicsComponent
{
public:
    DebugComponent(const QColor& color = QColor(0, 255, 255, 127), bool hasHitboxComponent = false, bool hasTextComponent = true,
                   const QString& debugText = "", const QString& name = "DebugComponent");

    void render(QPainter* painter) override;
    void update() override;
    void init() override;
private:
    const int DEBUG_ENTITY_WIDTH = 2000;
    const int DEBUG_ENTITY_HEIGHT = 2000;
    const int LINE_HEIGHT = 12;
    bool hasHitboxComponent;
    bool hasTextComponent;
    QColor color;
    QString debugText;
};

#endif // RECTANGLECOMPONENT_H
