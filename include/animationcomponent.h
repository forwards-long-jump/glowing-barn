#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H

#include <QVector>
#include <QPair>
#include <QString>

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

private: 
    QPixmap image;

    enum ButtonAnimationState {
        IDLE,
        START,
        ACTIVE,
        END
    };

    int currentAnimationStartingIndex;
    int currentAnimationVectorIndex;
    int currentFrameIndex;
    int ticksBeforeNextFrame;
    int frameWidth;
    int rotation = 0;

    bool loopingDisabled;
    bool mirrored;
    ButtonAnimationState currentButtonAnimationState;

    QVector<QString> requiredButtons;

    QVector<QPair<QString, QVector<float>>> animationProperties;
};

#endif // ANIMATIONCOMPONENT_H
