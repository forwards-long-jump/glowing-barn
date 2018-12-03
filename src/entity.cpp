#include "include/entity.h"

Entity::Entity(QGraphicsScene *scene):
    QGraphicsItem()
{
    scene->addItem(this);
}

Entity::~Entity()
{
    for (auto c : components)
    {
        delete c;
    }
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
