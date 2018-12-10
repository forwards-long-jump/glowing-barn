#include "include/physicscomponent.h"
#include "playerinputcomponent.h"
#include "playerstate.h"

PhysicsComponent::PhysicsComponent(QString name_, float accSpeed_, float jumpSpeed_, float g_, float friction_)
    :Component(name_),
      accSpeed(accSpeed_),
      jumpSpeed(jumpSpeed_),
      g(g_),
      friction(friction_)
{
    g = 0.4;
    accSpeed = 2;
    jumpSpeed = -10;
    dx = dy = 0;
    left = right = false;
}

void PhysicsComponent::update()
{
    if (left)   dx -= accSpeed;
    if (right)  dx += accSpeed;
    dx *= friction;
    ignoreGravityForTick = false;

    QPointF pos = getEntity()->pos();

    // DEBUG
    if(pos.y() > 950) {
        static_cast<PlayerInputComponent*>(getEntity()->getComponent("PlayerInputComponent"))->setState(&PlayerState::standing);
        getEntity()->setPos(pos.x() + dx, 950);
        dy = 0;
    }
    else {
        getEntity()->setPos(pos.x() + dx, pos.y() + dy);
    }

    if(!ignoreGravityForTick)
    {
        qDebug() << "Applying gravity";
        dy += g;
    }
    else
    {
        ignoreGravityForTick = false;
    }
}

void PhysicsComponent::disableGravityForTick()
{
    qDebug() << "Disable gravity for tick";
    ignoreGravityForTick = true;
}
