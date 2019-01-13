#ifndef TEXTCOMPONENT_H
#define TEXTCOMPONENT_H

#include "graphicscomponent.h"
#include "gamebuttoncomponent.h"

class TextComponent : public GraphicsComponent
{
public:
    TextComponent(const QString& text, QString buttons, int fontSize, QString name = "TextComponent");

    void update() override;
    void render(QPainter* painter) override;
private:
    const int MAX_BACKGROUND_OPACITY = 80;
    const int BORDER_OPACITY_OFFSET = 50;

    QString text;
    QVector<QString> requiredButtons;
    int fontSize;
    int currentBackgroundOpacity = 0;
};

#endif // TEXTCOMPONENT_H
