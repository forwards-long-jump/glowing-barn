#ifndef CAMERA_H
#define CAMERA_H

#include <QPointF>
#include <QGraphicsView>
#include <QRandomGenerator>
#include "entity.h"

// Manages what is displayed in screen per scene
class Camera
{
    const float DEFAULT_SCALING = 5;
    const float DEFAULT_SPEED = 0.2;
    const float DEFAULT_SPRING_CONSTANT_X = 1.8;
    const float DEFAULT_SPRING_CONSTANT_Y = 1.7;
    const bool DEFAULT_SPRING_EFFECT_ENABLED = true;
    const float MINIMUM_SPRING_FORCE_REQUIRED = 0.001;

public:
    Camera();
    ~Camera();

    // Called in Game to update camera calculations
    void update(QGraphicsView* v);
    // Center the camera on the position, use noSmoothing to teleport it
    void centerOn(QPointF pos, QSizeF screenSize, bool smoothTransition = true);
    void centerOn(float x, float y, QSizeF screenSize, bool smoothTransition = true);
    // Attach the camera to the entity, making it follow its center
    void attachTo(Entity* e);
    // Detach the current entity, keep the camera in place of where it was detached
    void detachEntity();
    // Update the speed coeff used when the camera moves
    void setSpeed(float speed_);
    // Changes the camera scaling instantly
    void setScaling(float scaling_);
    void setSpringEffectEnabled(bool enabled);
    void setBoundingRect(const QRectF rect);
    void setShakingIntensity(float f);

    QPointF getPosition() const;
    QRectF getBoundingRect() const;
    float getScaling() const;

    float getSpeed() const;

    Entity *getEntity() const;

    bool reachedTarget() const;

    QPointF getCameraForce() const;

private:
    Entity* entity;
    QPointF targetPosition;
    QPointF position;
    QPointF springConstant;
    QPointF cameraForce;
    QRectF cameraBoundingRect;
    bool springEffectEnabled;
    bool onTarget = false;
    float scaling;
    float speed;
    float shakeIntensity;


};

#endif // CAMERA_H
