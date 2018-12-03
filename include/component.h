#ifndef COMPONENT_H
#define COMPONENT_H

class Entity;

class Component
{
public:
    Component();
    virtual ~Component();

    void assignParent(Entity* parent) {entity = parent;}
    Entity* getEntity() const {return entity;}

    virtual void update() = 0;

protected:
    Entity* entity;
};

#include "include/entity.h"

#endif // COMPONENT_H
