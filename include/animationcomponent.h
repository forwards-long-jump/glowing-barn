#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H

#include <QVector>
#include <QPair>

#include "graphicscomponent.h"
#include "gamebuttoncomponent.h"

class AnimationComponent : public GraphicsComponent
{
public:
    AnimationComponent(const QString resourcePath, float frameWidth, QVector<QPair<QString, QVector<float>>> animationProperties,
                       QString buttons = "", const QString name = "AnimationComponent");

    static void addAnimationToVector(QString animationName, int frameCount, int framesDuration, QVector<QPair<QString, QVector<float>>> &animationVector);

    void setCurrentAnimation(QString animation);
    void disableLooping();
    void setMirrored(bool mirrored);

    void setButtons(QString buttons);
    void setButtons(QVector<QString> buttons);
    void setRotation(int value);

    void render(QPainter* painter) override;
    void update() override;

    void setSpeedMultiplier(int value);

    int getRotation() const;

private:
    QPixmap image;

    enum ButtonAnimationState {
        IDLE,
        START,
        ACTIVE,
        END
    };

    int currentAnimationStartingIndex = 0;
    int currentAnimationVectorIndex = 0;
    int currentFrameIndex = 0;
    int ticksBeforeNextFrame = 0;
    int frameWidth = 0;
    int rotation = 0;
    int speedMultiplier = 1;

    bool loopingDisabled = false;
    bool mirrored = false;
    ButtonAnimationState currentButtonAnimationState = ButtonAnimationState::IDLE;

    QVector<QString> requiredButtons;

    QVector<QPair<QString, QVector<float>>> animationProperties;
};

#endif // ANIMATIONCOMPONENT_H
