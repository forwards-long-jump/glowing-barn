#include "include/physicscomponent.h"
#include "playerinputcomponent.h"
#include "playerstate.h"
#include "squarehitboxcomponent.h"

PhysicsComponent::PhysicsComponent(float accSpeed_, float maxHSpeed_, float friction_, float jumpSpeed_, float g_, float maxVSpeed_, QString name_)
    :Component(name_),
      accSpeed(accSpeed_),
      maxHSpeed(maxHSpeed_),
      friction(friction_),
      jumpSpeed(jumpSpeed_),
      g(g_),
      maxVSpeed(maxVSpeed_)
{
    dx = dy = 0;
    left = right = false;
    ignorePhysicsForTick = false;
}

void PhysicsComponent::update()
{
    if (!ignorePhysicsForTick)
    {
        if (left)       dx -= accSpeed;
        else if (right) dx += accSpeed;
        else            dx *= friction;

        if (dx > maxHSpeed)         dx = maxHSpeed;
        else if (dx < - maxHSpeed)  dx = - maxHSpeed;

        dy += g;

        if (dy > maxVSpeed)
            dy = maxVSpeed;
        else if (dy < - maxVSpeed)
            dy = -maxVSpeed;
    }

    fdx *= forcedFrictionX;
    fdy *= forcedFrictionY;

    // Collisions
    onGround = false;
    for (HitboxComponent* hitbox : HitboxComponent::getInstancesOf("WallComponent"))
    {
        handleCollision(static_cast<SquareHitboxComponent*>(hitbox));
    } 

    QPointF pos = getEntity()->pos();
    if (!ignorePhysicsForTick)
    {
        getEntity()->setPos(pos.x() + dx + fdx, pos.y() + dy + fdy);
    }
    else
    {
        getEntity()->setPos(pos.x() + fdx, pos.y() + fdy);
        ignorePhysicsForTick = false;
    }
}

void PhysicsComponent::handleCollision(SquareHitboxComponent *hitbox)
{
    if (!hitbox) return;
    QRectF theirHB = hitbox->getHitbox();

    QRectF ourHB;
    for (auto physicsHitbox : HitboxComponent::getInstancesOf("PhysicsHitboxComponent"))
    {
        if (physicsHitbox->getEntity() == entity)
        {
            ourHB = static_cast<SquareHitboxComponent*>(physicsHitbox)->getHitbox();
        }
    }
    if (ourHB.isNull())
    {
        ourHB = QRectF(entity->pos(), entity->getSize());
    }

    if (ourHB.y() + ourHB.height() > theirHB.y() + 8 &&
        ourHB.y() < theirHB.y() + theirHB.height() - 8)
    {
        if (ourHB.x() + ourHB.width() + dx > theirHB.x() &&
            ourHB.x() < theirHB.x() + theirHB.width())
        {
            // RIGHT WALL
            getEntity()->setX(theirHB.x() - ourHB.width());
            dx = 0;
            fdx = 0;
        }
        if (ourHB.x() + dx < theirHB.x() + theirHB.width() &&
            ourHB.x() + ourHB.width() > theirHB.x() + theirHB.width())
        {
            // LEFT WALL
            getEntity()->setX(theirHB.x() + theirHB.width());
            dx = 0;
            fdx = 0;
        }

    }
    else if (ourHB.x() + ourHB.width() > theirHB.x() &&
             ourHB.x() < theirHB.x() + theirHB.width())
    {
        if (ourHB.y() + ourHB.height() + dy > theirHB.y() &&
            ourHB.y() < theirHB.y() + theirHB.height())
        {
            // FLOOR
            getEntity()->setY(theirHB.y() - ourHB.height());
            dy = 0;
            fdy = 0;
            onGround = true;
        }
        if (ourHB.y() + dy < theirHB.y() + theirHB.height() &&
            ourHB.y() + ourHB.height() > theirHB.y() + theirHB.height())
        {
            // CEILING
            getEntity()->setY(theirHB.y() + theirHB.height());
            dy *= - 0.2;
            fdy *= - 0.2;
        }
    }
}

void PhysicsComponent::disablePhysicsForTick()
{
    ignorePhysicsForTick = true;
}

QPointF PhysicsComponent::getSpeed() const
{
    return QPointF(dx, dy);
}

QPointF PhysicsComponent::getForcedSpeed() const
{
    return QPointF(fdx, fdy);
}
