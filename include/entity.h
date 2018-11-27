#ifndef ENTITY_H
#define ENTITY_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include "include/component.h"
#include "include/graphicscomponent.h"

class Entity : public QGraphicsItem
{
public:
    Entity(QGraphicsScene *parent, float width = 0.0, float height = 0.0);
    Entity(QGraphicsScene *parent, QSizeF size) : Entity(parent, size.width(), size.height()) {}

    virtual ~Entity();

    void addComponent(Component* c);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void update();

private:
    QVector<Component*> components;
    QSizeF size;
};

#endif // ENTITY_H
