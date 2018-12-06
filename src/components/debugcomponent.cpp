#include "include/debugcomponent.h"

DebugComponent::DebugComponent(QString name_, QString str, QColor c)
    :GraphicsComponent(name_)
{
    debugText = str;
    color = c;
}

void DebugComponent::render(QPainter *painter)
{
    painter->fillRect(0, 0, entity->getSize().width(), entity->getSize().height(), color);
    int currentLineHeight = 0;

    // Custom text
    if(debugText.length() > 0) {
        painter->drawText(QPoint(0, currentLineHeight += LINE_HEIGHT), QString("%0").arg(debugText));
    }

    // Position
    painter->drawText(QPoint(0, currentLineHeight += LINE_HEIGHT),
                      QString("(%0, %1) - %2x%3")
                        .arg(entity->x())
                        .arg(entity->y())
                        .arg(entity->boundingRect().width())
                        .arg(entity->boundingRect().height())
                     );
}

void DebugComponent::update() {
    //entity->setPos(entity->x() + 1, entity->y());
    //entity->moveBy(1, 0);
}
