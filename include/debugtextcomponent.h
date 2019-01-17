#ifndef DEBUGTEXTCOMPONENT_H
#define DEBUGTEXTCOMPONENT_H

#include "graphicscomponent.h"

/**
 * Component which draws text on the screen
 *
 * @authors Alexandre Bianchi, Pierre Bürki, Loïck Jeanneret
 */

class DebugTextComponent : public GraphicsComponent
{
public:
    DebugTextComponent(QString name, QString debugText, bool hasHitboxComponent = false);
    DebugTextComponent(QString debugText = "", bool hasHitboxComponent = false);

    void setText(const QString &text_);
    void render(QPainter* painter) override;
    void update() override;
private:
    const int LINE_HEIGHT = 12;
    QColor color;
    QString debugText;
    bool parentHasHitboxComponent;
};

#endif // DEBUGTEXTCOMPONENT_H
