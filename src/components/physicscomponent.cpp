#include "include/physicscomponent.h"


PhysicsComponent::PhysicsComponent(QString name_, float accSpeed_, float jumpSpeed_, float g_, float friction_)
    :Component(name_),
      accSpeed(accSpeed_),
      jumpSpeed(jumpSpeed_),
      g(g_),
      friction(friction_)
{
    dx = dy = 0;
    left = right = false;
}

void PhysicsComponent::update()
{
    if (left)   dx -= accSpeed;
    if (right)  dx += accSpeed;
    dx *= friction;
    dy += g;

    QPointF pos = getEntity()->pos();
    getEntity()->setPos(pos.x() + dx, pos.y() + dy);
}
