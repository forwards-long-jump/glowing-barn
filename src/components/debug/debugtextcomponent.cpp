#include "debugtextcomponent.h"

/**
 * @brief DebugTextComponent::DebugTextComponent
 * @param name_
 * @param str Text to display
 * @param hasHitboxComponent
 */
DebugTextComponent::DebugTextComponent(QString name_, QString str, bool hasHitboxComponent)
    : GraphicsComponent(name_)
{
    debugText = str;
    parentHasHitboxComponent = hasHitboxComponent;
}

/**
 * @brief DebugTextComponent::DebugTextComponent
 * @param str Text to display
 * @param hasHitboxComponent
 */
DebugTextComponent::DebugTextComponent(QString str,  bool hasHitboxComponent)
    : DebugTextComponent("DebugTextComponent", str, hasHitboxComponent)
{

}

/**
 * @brief DebugTextComponent::setText
 * @param text Text to display
 */
void DebugTextComponent::setText(const QString& text)
{
    debugText = text;
}

/**
 * @brief DebugTextComponent::render
 * @param painter
 */
void DebugTextComponent::render(QPainter* painter)
{
    int currentLineHeight = 0;

    if(parentHasHitboxComponent) {
        currentLineHeight += LINE_HEIGHT;
    }

    // Entity position
    QRectF rect(parent->x(), parent->y(), parent->boundingRect().width(), parent->boundingRect().height());

    // Custom text
    if(debugText.length() > 0)
    {
        painter->drawText(QPoint(0, currentLineHeight += LINE_HEIGHT), QString("%0").arg(debugText));
    }

    Entity* parentEntity = nullptr;
    if(this->getParent()->parentItem()) {
        parentEntity = static_cast<Entity*>(this->getParent()->parentItem());
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

/**
 * @brief DebugTextComponent::update
 */
void DebugTextComponent::update()
{

}
