#ifndef ENTITY_H
#define ENTITY_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include "include/component.h"
#include "include/graphicscomponent.h"

class Entity : public QGraphicsItem
{
public:
    Entity(QGraphicsScene* parent);
    virtual ~Entity();

    void addComponent(Component* c);

    QRectF boundingRect() const {return QRectF(pos(), QPointF(10,10));}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    QVector<Component*> components;
};

#endif // ENTITY_H
