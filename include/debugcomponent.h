#ifndef RECTANGLECOMPONENT_H
#define RECTANGLECOMPONENT_H

#include "include/graphicscomponent.h"
#include "debugtextcomponent.h"

class DebugComponent : public GraphicsComponent
{
public:
    DebugComponent(QString name = "DebugComponent", QString debugText = "", QColor color = QColor(0, 255, 255, 127));
    DebugComponent(QString str, QColor c);

    void render(QPainter* painter) override;
    void update() override;
    void init() override;
private:
    const int LINE_HEIGHT = 12;
    QColor color;
    QString debugText;
};

#endif // RECTANGLECOMPONENT_H
