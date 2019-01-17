#ifndef COMPONENT_H
#define COMPONENT_H

#include <QString>

class Entity;

/**
 * Basis of the Entity-Components design pattern
 *
 * @authors Alexandre Bianchi, Pierre Bürki, Loïck Jeanneret
 */

class Component
{
public:
    Component(const QString& name = "DEFAULT");
    virtual ~Component();

    void setParent(Entity* parent);

    Entity* getParent() const;
    QString getName() const;

    virtual void update() = 0;
    virtual void init();
    virtual void onEnable();
    virtual void onDisable();

protected:
    QString name = "";
    Entity* parent = nullptr;
};

#include "include/entity.h"

#endif // COMPONENT_H
