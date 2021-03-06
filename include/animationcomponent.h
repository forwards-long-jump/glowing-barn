#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H

#include <QVector>
#include <QPair>

#include "graphicscomponent.h"

/**
 * Allows its entity to have an animated sprite
 *
 * @authors Alexandre Bianchi, Pierre Bürki, Loïck Jeanneret
 */

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

    bool getMirrored() const;

    bool getTiled() const;
    void setTiled(bool value);

    bool getMirroredY() const;
    void setMirroredY(bool value);

    void setImage(const QPixmap &value);

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
    bool tiled = false;

    bool loopingDisabled = false;
    bool mirrored = false;
    bool mirroredY = false;
    ButtonAnimationState currentButtonAnimationState = ButtonAnimationState::IDLE;

    QVector<QString> requiredButtons;

    QVector<QPair<QString, QVector<float>>> animationProperties;
};

#include "gamebuttoncomponent.h"

#endif // ANIMATIONCOMPONENT_H
