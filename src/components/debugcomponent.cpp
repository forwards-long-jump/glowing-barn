#include "include/debugcomponent.h"

DebugComponent::DebugComponent(QString str, QColor c)
{
    debugText = str;
    color = c;
}

void DebugComponent::render(QPainter *painter)
{
    painter->fillRect(entity->boundingRect(), color);
    int currentLineHeight = 0;

    if(debugText.length() > 0) {
        painter->drawText(entity->pos() + QPoint(0, currentLineHeight += LINE_HEIGHT), QString("%0").arg(debugText));
    }

    painter->drawText(entity->pos() + QPoint(0, currentLineHeight += LINE_HEIGHT),
                      QString("(%0, %1) - %2x%3")
                        .arg(entity->boundingRect().x())
                        .arg(entity->boundingRect().y())
                        .arg(entity->boundingRect().width())
                        .arg(entity->boundingRect().height())
                     );
}

void DebugComponent::update() {}
