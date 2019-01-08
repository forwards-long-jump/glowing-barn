#include "particle.h"

Particle::Particle(float dx, float dy, int w, int h, int lifetime, void (*particleRender)(QPainter* painter, Particle* particle), int index) :
    dx(dx), dy(dy), index(index),
    boundingRectangle(0, 0, w, h), lifetime(lifetime),
    particleRender(particleRender) {}

QRectF Particle::boundingRect() const
{
    return boundingRectangle;
}

void Particle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    particleRender(painter, this);
}

int Particle::getLifetime() const
{
    return lifetime;
}

void Particle::decrementLifetime()
{
    lifetime--;
}

int Particle::getIndex() const
{
    return index;
}

float Particle::getDy() const
{
    return dy;
}

void Particle::setDy(float value)
{
    dy = value;
}

float Particle::getDx() const
{
    return dx;
}

void Particle::setDx(float value)
{
    dx = value;
}
