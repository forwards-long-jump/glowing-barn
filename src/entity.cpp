#include "include/entity.h"
#include <QDebug>

Entity::Entity(QGraphicsScene *scene):
    QGraphicsItem()
{
    scene->addItem(this);
}

void Entity::addComponent(Component* c)
{
    c->AssignParent(this);
    components.push_back(c);
}

void Entity::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    qDebug() << "lel";
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
