#include "../include/camera.h"

Camera::Camera()
{
    position = QPointF(0,0);
    targetPosition = QPointF(0, 0);
    scaling = DEFAULT_SCALING;
    speed = DEFAULT_SPEED;
    entity = nullptr;
}

Camera::~Camera()
{

}

void Camera::update(QGraphicsView *v)
{
    if(entity != nullptr) {
        targetPosition.setX(entity->pos().x());
        targetPosition.setY(entity->pos().y());
    }
    position += (targetPosition - position) * speed;

    v->resetTransform();
    v->scale(scaling, scaling);
    v->setSceneRect(-position.x(), -position.y(), v->width() / scaling, v->height() / scaling);
}

void Camera::centerOn(QPointF pos, bool noSmoothing)
{
    detachEntity();
    if(noSmoothing) {
        targetPosition = pos;
    }
    else {
        targetPosition = pos;
        position = pos;
    }
}

void Camera::attachTo(Entity *e)
{
    entity = e;
}

void Camera::detachEntity()
{
    entity = nullptr;
}

void Camera::setSpeed(float speed_)
{
    speed = speed_;
}

void Camera::setScaling(float scaling_)
{
    scaling = scaling_;
}
