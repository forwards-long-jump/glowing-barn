#ifndef DEBUGTEXTCOMPONENT_H
#define DEBUGTEXTCOMPONENT_H

#include "graphicscomponent.h"

class DebugTextComponent : public GraphicsComponent
{
public:
    DebugTextComponent(QString name, QString debugText);
    DebugTextComponent(QString debugText = "");

    void render(QPainter* painter) override;
    void update() override;
private:
    const int LINE_HEIGHT = 12;
    QColor color;
    QString debugText;
};

#endif // DEBUGTEXTCOMPONENT_H
