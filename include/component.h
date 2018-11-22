#ifndef COMPONENT_H
#define COMPONENT_H

class Entity;

class Component
{
public:
    Component();
    ~Component();

    void assignParent(Entity* parent) {entity = parent;}

    virtual void update() = 0;

protected:
    Entity* entity;
};

#include "include/entity.h"

#endif // COMPONENT_H
