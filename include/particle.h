#ifndef PARTICLE_H
#define PARTICLE_H

#include "entity.h"

class Particle : public Entity
{
public:
    Particle(float dx, float dy, int w, int h, int lifetime, void (*particleRender)(QPainter* painter, Particle* particle), int index);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    float getDx() const;
    void setDx(float value);
    float getDy() const;
    void setDy(float value);
    int getLifetime() const;
    void decrementLifetime();

    int getIndex() const;

private:
    float dx = 0;
    float dy = 0;
    int index = 0;
    int lifetime = 0;
    QRectF boundingRectangle;
    void (*particleRender)(QPainter* painter, Particle* particle);
};

#endif // PARTICLE_H
