#ifndef COMPONENT_H
#define COMPONENT_H

#include <QWidget>

class Entity;

class Component
{
public:
    Component();
    ~Component();

    void AssignParent(Entity* parent) {entity = parent;}

    virtual void update() = 0;

protected:
    Entity* entity;
};

#include "include/entity.h"

#endif // COMPONENT_H
