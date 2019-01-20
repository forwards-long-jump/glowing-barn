#ifndef PARALLAXCOMPONENT_H
#define PARALLAXCOMPONENT_H

#include <QPointF>

#include "component.h"
#include "gamescene.h"

/**
 * Allow its entity to move with a certain parallax when the camera moves
 *
 * @authors Alexandre Bianchi, Pierre Bürki, Loïck Jeanneret
 */

class ParallaxComponent  : public Component
{
public:
    ParallaxComponent(QPointF coeff, QString name = "ParallaxComponent");
    ParallaxComponent(float coeff, QString name = "ParallaxComponent") : ParallaxComponent(QPointF(coeff, coeff), name){}

    void update() override;
    void init() override;

    void setAnchor(QPointF p);

private:
    QPointF anchorPos;
    QPointF coeff;
};

#endif // PARALLAXCOMPONENT_H
