#include "include/entity.h"

/**
 * @brief Entity::Entity
 * @param parent
 * @param x
 * @param y
 * @param width
 * @param height
 */
Entity::Entity(QGraphicsItem* parent, float x, float y, float width, float height) : QGraphicsItem(parent)
{
    setPos(x, y);
    size.setWidth(width);
    size.setHeight(height);

    components = new QMap<QString, Component*>();
    disabledComponents = new QMap<QString, Component*>();
}

/**
 * @brief Entity::~Entity
 */
Entity::~Entity()
{
    qDeleteAll(*components);
    delete components;
}

/**
 * @brief Entity::boundingRect
 * @return
 */
QRectF Entity::boundingRect() const
{
    return QRectF(0, 0, size.width(), size.height());
}

/**
 * @brief Adds a component to this entity and init it
 * @param c
 */
void Entity::addComponent(Component* c)
{
    c->setParent(this);
    components->insert(c->getName(), c);
    c->init();
}

/**
 * @brief Prevents a component to be updated / rendered temporarily
 * @param name
 * @return
 */
bool Entity::disableComponent(QString name)
{
    if (components->contains(name))
    {
        Component* c = components->value(name);
        disabledComponents->insert(c->getName(), c);
        c->onDisable();
        components->remove(name);
        return true;
    }
    return false;
}

/**
 * @brief Enable a component previously disabled using disableComponent
 * @param name
 * @return
 */
bool Entity::enableComponent(QString name)
{
    if (disabledComponents->contains(name))
    {
        Component* c = disabledComponents->value(name);
        components->insert(c->getName(), c);
        c->onEnable();
        disabledComponents->remove(name);
        return true;
    }
    return false;
}

/**
 * @brief Get a component by its associated name
 * @param name
 * @return
 */
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

/**
 * @brief Get all *enabled* components of this entity
 * @return
 */
QMap<QString, Component*>*Entity::getComponents()
{
    return components;
}

/**
 * @brief Entity::update
 */
void Entity::update()
{
    for (auto c : components->values())
    {
        c->update();
    }
}

/**
 * @brief Entity::getSize
 * @return
 */
QSizeF Entity::getSize() const
{
    return size;
}

/**
 * @brief Entity::paint
 * @param painter
 * @param option
 * @param widget
 */
void Entity::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
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
