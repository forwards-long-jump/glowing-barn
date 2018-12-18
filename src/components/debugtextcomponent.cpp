#include "debugtextcomponent.h"

DebugTextComponent::DebugTextComponent(QString name_, QString str, bool hasHitboxComponent) : GraphicsComponent(name_)
{
    debugText = str;
    parentHasHitboxComponent = hasHitboxComponent;
}

DebugTextComponent::DebugTextComponent(QString str,  bool hasHitboxComponent) : DebugTextComponent("DebugTextComponent", str, hasHitboxComponent)
{

}

void DebugTextComponent::setText(const QString &text_)
{
    debugText = text_;
}

void DebugTextComponent::render(QPainter *painter)
{
    int currentLineHeight = 0;

    if(parentHasHitboxComponent) {
        currentLineHeight += LINE_HEIGHT;
    }

    // Entity position
    QRectF rect(entity->x(), entity->y(), entity->boundingRect().width(), entity->boundingRect().height());

    // Custom text
    if(debugText.length() > 0)
    {
        painter->drawText(QPoint(0, currentLineHeight += LINE_HEIGHT), QString("%0").arg(debugText));
    }

    Entity* parentEntity = nullptr;
    if(this->getEntity()->parentItem()) {
        parentEntity = static_cast<Entity*>(this->getEntity()->parentItem());
        rect.setRect(parentEntity->pos().x(), parentEntity->pos().y(), parentEntity->boundingRect().width(), parentEntity->boundingRect().height());

        // Component list
        QMap<QString, Component*>* dhc = parentEntity->getComponents();
        QMap<QString, Component*>::const_iterator i = dhc->constBegin();
        QString componentList = "";

        while (i != dhc->constEnd()) {
            componentList.append(i.key() + ", ");
            ++i;
        }

        painter->drawText(QPoint(0, currentLineHeight += LINE_HEIGHT), QString("%0").arg(componentList));
    }

    // Position
    painter->drawText(QPoint(0, currentLineHeight += LINE_HEIGHT),
                      QString("(%0, %1) - %2x%3")
                        .arg(rect.x())
                        .arg(rect.y())
                        .arg(rect.width())
                        .arg(rect.height())
                     );
}

void DebugTextComponent::update()
{

}
