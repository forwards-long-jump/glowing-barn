#ifndef CAMERA_H
#define CAMERA_H

#include <QPointF>
#include <QGraphicsView>
#include "entity.h"

// Manages what is displayed in screen per scene
class Camera
{
    const float DEFAULT_SCALING = 5;
    const float DEFAULT_SPEED = 0.2;

public:
    Camera();
    ~Camera();

    // Called in Game to update camera calculations
    void update(QGraphicsView *v);
    // Center the camera on the position, use noSmoothing to teleport it
    void centerOn(QPointF pos, bool noSmoothing = false);
    void centerOn(float x, float y, bool noSmoothing = false);
    // Attach the camera to the entity, making it follow its center
    void attachTo(Entity *e);
    // Detach the current entity, keep the camera in place of where it was detached
    void detachEntity();
    // Update the speed coeff used when the camera moves
    void setSpeed(float speed_);
    // Changes the camera scaling
    void setScaling(float scaling_);

private:
    Entity *entity;
    QPointF targetPosition;
    QPointF position;
    float scaling;
    float speed;


};

#endif // CAMERA_H
