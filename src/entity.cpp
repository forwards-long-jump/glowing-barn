#include "include/entity.h"

Entity::Entity(QGraphicsItem *parent, float width, float height)
    : QGraphicsItem(parent)
{
    size.setWidth(width);
    size.setHeight(height);
}

Entity::~Entity()
{
    qDeleteAll(components);
}

QRectF Entity::boundingRect() const
{
    return QRectF(0, 0, size.width(), size.height());
}

void Entity::addComponent(Component* c)
{
    c->assignParent(this);
    components.push_back(c);
}

void Entity::update()
{
    for (auto c : components)
    {
        c->update();
    }
}

QSizeF Entity::getSize()
{
    return size;
}

void Entity::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    for (auto c : components)
    {
        // Determining whether this component is a graphical one
        GraphicsComponent* component = dynamic_cast<GraphicsComponent*>(c);
        if (component)
        {
            component->render(painter);
        }
    }
}
