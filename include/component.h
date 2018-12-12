#ifndef COMPONENT_H
#define COMPONENT_H

#include <QString>

class Entity;

class Component
{
public:
    Component(QString name_ = "DEFAULT");
    virtual ~Component();

    void assignParent(Entity* parent) {entity = parent;}
    Entity* getEntity() const {return entity;}
    QString getName() const {return name;}

    virtual void update() = 0;
    virtual void init() {}

protected:
    Entity* entity;

    QString name;
};

#include "include/entity.h"

#endif // COMPONENT_H
