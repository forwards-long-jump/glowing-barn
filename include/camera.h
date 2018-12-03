#ifndef CAMERA_H
#define CAMERA_H

#include "QPointF"
#include "entity.h"
#include "QGraphicsView";

class Camera
{
    const float DEFAULT_SCALING = 1;
    const float DEFAULT_SPEED = 1;

public:
    Camera();
    ~Camera();

    void update(QGraphicsView *v);
    void centerOn(QPointF pos, bool noSmoothing = false);
    void attachTo(Entity *e);
    void detachEntity();
    void setSpeed(float speed_);
    void setScaling(float scaling_);

private:
    Entity *entity;
    QPointF targetPosition;
    QPointF position;
    float scaling;
    float speed;


};

#endif // CAMERA_H
