#ifndef RECTANGLECOMPONENT_H
#define RECTANGLECOMPONENT_H

#include "include/graphicscomponent.h"

class DebugComponent : public GraphicsComponent
{
public:
    DebugComponent(QString debugText = "", QColor color = QColor(0, 255, 255, 127));

    void render(QPainter* painter) override;
    void update() override;
private:
    const int LINE_HEIGHT = 12;
    QColor color;
    QString debugText;
};

#endif // RECTANGLECOMPONENT_H
