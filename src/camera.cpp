#include "camera.h"

/**
 * @brief Camera::Camera
 */
Camera::Camera()
{
    cameraBoundingRect = QRectF(0, 0, 0, 0);
    position = QPointF(0,0);
    targetPosition = QPointF(0, 0);
    cameraForce = QPointF(0, 0);
    scaling = DEFAULT_SCALING;
    speed = DEFAULT_SPEED;
    springConstant = QPointF(DEFAULT_SPRING_CONSTANT_X, DEFAULT_SPRING_CONSTANT_Y);
    springEffectEnabled = DEFAULT_SPRING_EFFECT_ENABLED;
    entity = nullptr;
    shakeIntensity = 0;
}

/**
 * @brief Camera::~Camera
 */
Camera::~Camera()
{

}

/**
 * @brief Camera::update
 * @param view
 */
void Camera::update(QGraphicsView* v)
{
    if(entity != nullptr)
    {
        targetPosition.setX(entity->pos().x() + entity->getSize().width() / 2);
        targetPosition.setY(entity->pos().y() + entity->getSize().height() / 2);
    }

    QPointF screenCenter(v->width() / scaling / 2, v->height() / scaling / 2);

    // Handle camera boundaries
    if(cameraBoundingRect.width() + cameraBoundingRect.height() != 0) {
        if(targetPosition.y() + screenCenter.y() > cameraBoundingRect.bottom())
        {
            targetPosition.setY(cameraBoundingRect.bottom() -screenCenter.y());
        }

        if(targetPosition.x() + screenCenter.x() > cameraBoundingRect.right())
        {
            targetPosition.setX(cameraBoundingRect.right() - screenCenter.x());
        }

        if(targetPosition.y() -screenCenter.y() < cameraBoundingRect.top())
        {
            targetPosition.setY(cameraBoundingRect.top() + screenCenter.y());
        }

        if(targetPosition.x() - screenCenter.x() < cameraBoundingRect.left())
        {
            targetPosition.setX(cameraBoundingRect.left() + screenCenter.x());
        }

        // If the scene is too small for the defined boundingRect, center it on it
        if(v->width() / scaling > cameraBoundingRect.width())
        {
             targetPosition.setX(cameraBoundingRect.center().x());
        }

        if(v->height() / scaling  > cameraBoundingRect.height())
        {
             targetPosition.setY(cameraBoundingRect.center().y());
        }
    }

    if(springEffectEnabled)
    {
        cameraForce += (targetPosition - position - QPointF(v->width() / scaling / 2, v->height() / scaling / 2)) * speed;
        cameraForce.setX(cameraForce.x() / springConstant.x());
        cameraForce.setY(cameraForce.y() / springConstant.y());

        if(qAbs(cameraForce.x()) < MINIMUM_SPRING_FORCE_REQUIRED) cameraForce.setX(0);
        if(qAbs(cameraForce.y()) < MINIMUM_SPRING_FORCE_REQUIRED) cameraForce.setY(0);

        position += cameraForce;
    }
    else
    {
        position += (targetPosition - position - QPointF(v->width() / scaling / 2, v->height() / scaling / 2)) * speed;
    }

    if(cameraBoundingRect.width() + cameraBoundingRect.height() != 0) {
        if(v->width() / scaling < cameraBoundingRect.width()) {
            if(position.x() < cameraBoundingRect.left())
            {
                position.setX(cameraBoundingRect.left());
            }

            if(position.x() + v->width() / scaling > cameraBoundingRect.right())
            {
                position.setX(cameraBoundingRect.right() - v->width() / scaling);
            }
        }

        if(v->height() / scaling  < cameraBoundingRect.height()) {
            if(position.y() < cameraBoundingRect.top())
            {
                position.setY(cameraBoundingRect.top());
            }

            if(position.y() + v->height() / scaling > cameraBoundingRect.bottom())
            {
                position.setY(cameraBoundingRect.bottom() - v->height() / scaling);
            }
        }

    }

    if(shakeIntensity != 0)
    {
        position.setX(position.x() + QRandomGenerator::global()->generateDouble() * shakeIntensity);
        position.setY(position.y() + QRandomGenerator::global()->generateDouble() * shakeIntensity);
    }

    if((position - targetPosition + screenCenter).manhattanLength() < 5) onTarget = true;

    v->resetTransform();
    v->scale(scaling, scaling);

    v->setSceneRect(position.x(), position.y(), v->width() / scaling, v->height() / scaling);
}

/**
 * @brief Camera::centerOn
 * @param position
 * @param screenSize
 * @param smoothTransition
 */
void Camera::centerOn(QPointF pos, QSizeF screenSize, bool smoothTransition)
{
    detachEntity();
    targetPosition = pos - QPointF(screenSize.width() / scaling / 2.0, screenSize.height() / scaling / 2.0);

    if(!smoothTransition) {
        position = targetPosition;
        cameraForce.setX(0);
        cameraForce.setY(0);
    }
}

/**
 * @brief Camera::centerOn
 * @param x
 * @param y
 * @param screenSize
 * @param smoothTransition
 */
void Camera::centerOn(float x, float y, QSizeF screenSize, bool smoothTransition)
{
    centerOn(QPointF(x, y), screenSize, smoothTransition);
}

/**
 * @brief Camera::attachTo
 * The camera will follow this entity
 * @param entity
 */
void Camera::attachTo(Entity* e)
{
    onTarget = false;
    entity = e;
}

/**
 * @brief Camera::detachEntity
 */
void Camera::detachEntity()
{
    entity = nullptr;
}

/**
 * @brief Camera::setSpeed
 * @param speed_
 */
void Camera::setSpeed(float speed_)
{
    speed = speed_;
}

/**
 * @brief Camera::setScaling
 * @param scaling_
 */
void Camera::setScaling(float scaling_)
{
    if (scaling_ > 0)
        scaling = scaling_;
}

/**
 * @brief Camera::setSpringEffectEnabled
 * @param enabled
 */
void Camera::setSpringEffectEnabled(bool enabled)
{
    springEffectEnabled = enabled;
}

/**
 * @brief Camera::setBoundingRect
 * @param rect
 */
void Camera::setBoundingRect(const QRectF rect)
{
    cameraBoundingRect = rect;
}

/**
 * @brief Camera::setShakingIntensity
 * @param f
 */
void Camera::setShakingIntensity(float f)
{
    shakeIntensity = f;
}

/**
 * @brief Camera::getBoundingRect
 * @return
 */
QRectF Camera::getBoundingRect() const
{
    return cameraBoundingRect;
}

/**
 * @brief Camera::getPosition
 * @return
 */
QPointF Camera::getPosition() const
{
    return position;
}

/**
 * @brief Camera::getScaling
 * @return
 */
float Camera::getScaling() const
{
    return scaling;
}

/**
 * @brief Camera::getSpeed
 * @return
 */
float Camera::getSpeed() const
{
    return speed;
}

/**
 * @brief Camera::getEntity
 * @return
 */
Entity *Camera::getEntity() const
{
    return entity;
}

/**
 * @brief Camera::reachedTarget
 * @return
 */
bool Camera::reachedTarget() const
{
    return onTarget;
}

/**
 * @brief Camera::getCameraForce
 * @return
 */
QPointF Camera::getCameraForce() const
{
    return cameraForce;
}
