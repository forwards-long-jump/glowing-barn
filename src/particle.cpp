#include "particle.h"

/**
 * @brief Particle::Particle
 * @param dx
 * @param dy
 * @param width
 * @param height
 * @param lifetime
 * @param index
 */
Particle::Particle(float dx, float dy, int w, int h, int lifetime, void (*particleRender)(QPainter* painter, Particle* particle), int index)
    : Entity(nullptr, 0, 0, w, h),
      dx(dx), dy(dy),
      index(index),
      lifetime(lifetime),
      boundingRectangle(0, 0, w, h),
      particleRender(particleRender)
{

}

/**
 * @brief Particle::boundingRect
 * @return
 */
QRectF Particle::boundingRect() const
{
    return boundingRectangle;
}

/**
 * @brief Particle::paint
 * @param painter
 * @param option
 * @param widget
 */
void Particle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    particleRender(painter, this);
}

/**
 * @brief Particle::getLifetime
 * @return
 */
int Particle::getLifetime() const
{
    return lifetime;
}

/**
 * @brief Particle::decrementLifetime
 */
void Particle::decrementLifetime()
{
    lifetime--;
}

/**
 * @brief Particle::getIndex
 * @return
 */
int Particle::getIndex() const
{
    return index;
}

/**
 * @brief Particle::getDy
 * @return
 */
float Particle::getDy() const
{
    return dy;
}

/**
 * @brief Particle::setDy
 * @param value
 */
void Particle::setDy(float value)
{
    dy = value;
}

/**
 * @brief Particle::getDx
 * @return
 */
float Particle::getDx() const
{
    return dx;
}

/**
 * @brief Particle::setDx
 * @param value
 */
void Particle::setDx(float value)
{
    dx = value;
}
