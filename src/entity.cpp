#include "include/entity.h"

Entity::Entity(QGraphicsItem *parent, float width, float height)
    : QGraphicsItem(parent)
{
    size.setWidth(width);
    size.setHeight(height);
    components = new QMap<QString, Component*>();
}

Entity::~Entity()
{
    qDeleteAll(*components);
    delete components;
}

QRectF Entity::boundingRect() const
{
    return QRectF(0, 0, size.width(), size.height());
}

void Entity::addComponent(Component* c)
{
    c->assignParent(this);
    components->insert(c->getName(), c);
    c->init();
}

Component* Entity::getComponent(QString name) const
{

    if (components->contains(name))
    {
        Component* ret = components->value(name);
        return ret;
    }
    else
    {
        return nullptr;
    }
}

QMap<QString, Component *> *Entity::getComponents()
{
    return components;
}

void Entity::update()
{
    for (auto c : components->values())
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
    for (auto c : components->values())
    {
        // Determining whether this component is a graphical one
        GraphicsComponent* component = dynamic_cast<GraphicsComponent*>(c);
        if (component)
        {
            component->render(painter);
        }
    }
}
