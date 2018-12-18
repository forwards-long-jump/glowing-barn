#ifndef ENTITY_H
#define ENTITY_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QMap>
#include "component.h"
#include "graphicscomponent.h"

class Entity : public QGraphicsItem
{
public:
    Entity(QGraphicsItem *parent = nullptr, float width = 0.0, float height = 0.0);
    Entity(QGraphicsItem *parent, QSizeF size) : Entity(parent, size.width(), size.height()) {}

    virtual ~Entity();

    void update();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void addComponent(Component* c);
    bool disableComponent(QString name);
    bool enableComponent(QString name);
    Component* getComponent(QString name) const;
    QMap<QString, Component*>* getComponents();

    QSizeF getSize();
    QRectF boundingRect() const;
private:
    QMap<QString, Component*>* components;
    QMap<QString, Component*>* disabledComponents;
    QSizeF size;
};

#endif // ENTITY_H
