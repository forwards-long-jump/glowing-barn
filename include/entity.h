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

    QRectF boundingRect() const {return QRectF(pos(), QPointF(10,10));} // TODO: Allow a component to change that
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void update();

    void addDdx(float dx_) {dx += dx_;}
    void addDdy(float dy_) {dy += dy_;}
    float getDx() const {return dx;}
    float getDy() const {return dy;}

private:
    QVector<Component*> components;

    float dx;
    float dy;
};

#endif // ENTITY_H
