#ifndef ENTITY_H
#define ENTITY_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QMap>

#include "component.h"
#include "graphicscomponent.h"

/**
 * Basis of the Entity-Components design pattern
 *
 * @authors Alexandre Bianchi, Pierre Bürki, Loïck Jeanneret
 */

class Entity : public QGraphicsItem
{
public:
    Entity(QGraphicsItem* parent = nullptr, float x = 0, float y = 0, float width = 0.0, float height = 0.0);
    Entity(QGraphicsItem* parent, QSizeF size, QPointF position = QPointF(0, 0))
        : Entity(parent, position.x(), position.y(), size.width(), size.height()) {}
    Entity(QGraphicsItem* parent, QPointF position, QSizeF size = QSizeF(0, 0))
        : Entity(parent, position.x(), position.y(), size.width(), size.height()) {}

    virtual ~Entity();

    void update();
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    void addComponent(Component* c);
    bool disableComponent(QString name);
    bool enableComponent(QString name);
    Component* getComponent(QString name) const;
    QMap<QString, Component*>* getComponents();

    QSizeF getSize() const;
    QRectF boundingRect() const;
    bool shouldBeDeleted() const;
    void deleteLater();

    Entity *getParent() const;

private:
    QMap<QString, Component*>* components;
    QMap<QString, Component*>* disabledComponents;
    QSizeF size;
    Entity* parent = nullptr;
    bool markedForDeletion = false;
};

#endif // ENTITY_H
