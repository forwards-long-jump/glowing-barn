#ifndef CAMERASEQUENCECOMPONENT_H
#define CAMERASEQUENCECOMPONENT_H

#include "scene.h"
#include "gamebuttoncomponent.h"

/**
 * Detaches the camera off of the player in order to play cinematic sequences
 *
 * @authors Alexandre Bianchi, Pierre Bürki, Loïck Jeanneret
 */

class CameraSequenceComponent : public Component
{
public:
    CameraSequenceComponent(QString buttons, float cameraSpeed, int lockCameraDuration, bool lockPlayerInput, bool playOnce, QString name = "CameraSequenceComponent");

    void update() override;
private:
    QVector<QString> requiredButtons;
    Entity* previousEntity;
    float previousSpeed = -1.0f;
    float cameraSpeed = 1.0f;
    int lockCameraDuration = 0;
    int enabledDurationInTick = -1;
    bool sequenceEnded = true;
    bool lockPlayerInput = false;
    bool playOnce = true;
    bool playedOnce = false;
};

#endif // CAMERASEQUENCECOMPONENT_H
