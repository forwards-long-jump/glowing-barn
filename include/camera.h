#ifndef CAMERA_H
#define CAMERA_H

#include "QPointF"
#include "entity.h"


class Camera
{
public:
    Camera();
    ~Camera();

    void update();
    void centerOn(QPointF pos, bool noSmoothing = false);
    void attachTo(Entity *e);
    void detachEntity();
    void setSpeed(float speed_);
    void setScaling(float scaling_);

private:
    QPointF targetPosition;
    QPointF position;
    float scaling;
    float speed;


};

#endif // CAMERA_H
