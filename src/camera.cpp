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
        targetPosition.setX(entity->pos().x() + entity->getSize().width() / 2);
        targetPosition.setY(entity->pos().y() + entity->getSize().height() / 2);
    }
    position += (targetPosition - position - QPointF(v->width() / scaling / 2, v->height() / scaling / 2)) * speed;
    //position = targetPosition;

    v->resetTransform();
    v->scale(scaling, scaling);
    //v->centerOn(targetPosition);
    v->setSceneRect(position.x(), position.y(), v->width() / scaling, v->height() / scaling);
}

void Camera::centerOn(QPointF pos, bool noSmoothing)
{
    detachEntity();
    targetPosition = pos;
    if(!noSmoothing) {
        position = pos;
    }
}

void Camera::centerOn(float x, float y, bool noSmoothing)
{
    centerOn(QPointF(x, y), noSmoothing);
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
