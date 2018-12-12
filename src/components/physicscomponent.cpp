#include "include/physicscomponent.h"
#include "playerinputcomponent.h"
#include "playerstate.h"
#include "hitboxcomponent.h"

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

    dy += g;
    dy *= friction;

    QPointF pos = getEntity()->pos();
    getEntity()->setPos(pos.x() + dx, pos.y() + dy);

    // Collisions
    for (HitboxComponent* hitbox : HitboxComponent::getInstancesOf("WallComponent"))
    {
        handleCollision(hitbox);
    }
}

void PhysicsComponent::handleCollision(HitboxComponent *hitbox)
{
    if (!hitbox) return;
    QRectF theirHB = hitbox->getHitbox();

    QRectF ourHB;
    HitboxComponent* ours = static_cast<HitboxComponent*> (entity->getComponent("HitboxComponent"));
    if (ours)
    {
        ourHB = ours->getHitbox();
    }
    else
    {
        ourHB = QRectF(entity->pos(), entity->getSize());
    }

    if (ourHB.intersects(theirHB))
    {
        QRectF inter = ourHB & theirHB;
        if (inter.height() <= inter.width())
        {
            if (dy >= 0)
            {
                getEntity()->setY(getEntity()->pos().y() - inter.height());
                dy = 0;
                onGround = true;
            }
            else
            {
                getEntity()->setY(getEntity()->pos().y() + inter.height());
                dy *= - 0.2;
            }
        }
        else
        {
            if (dx > 0)
            {
                getEntity()->setX(getEntity()->pos().x() - inter.width());
            }
            else
            {
                getEntity()->setX(getEntity()->pos().x() + inter.width());
            }
            dx *= - 0.2;
        }
    }
}
