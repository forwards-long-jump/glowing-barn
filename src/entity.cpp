#include "include/entity.h"

Entity::Entity(QGraphicsScene *scene):
    QGraphicsItem()
{
    scene->addItem(this);
}

void Entity::addComponent(Component* c)
{
    c->assignParent(this);
    components.push_back(c);
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
