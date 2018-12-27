#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H

#include <QVector>
#include <QPair>
#include <QString>

#include "graphicscomponent.h"

class AnimationComponent : public GraphicsComponent
{
public:
    AnimationComponent(const QString resourceName, float frameWidth, QVector<QPair<QString, QVector<float>>> animationProperties,
                       const QString name = "AnimationComponent");

    static void addAnimationToVector(QString animationName, int frameCount, int framesDuration, QVector<QPair<QString, QVector<float>>> &animationVector);

    void setCurrentAnimation(QString animation);
    void disableLooping();
    void setMirrored(bool mirrored);

    void render(QPainter* painter) override;
    void update() override;

private:
    QPixmap image;

    int currentAnimationStartingIndex;
    int currentAnimationVectorIndex;
    int currentFrameIndex;
    int ticksBeforeNextFrame;
    int frameWidth;

    bool loopingDisabled;
    bool mirrored = true;



    QVector<QPair<QString, QVector<float>>> animationProperties;
};

#endif // ANIMATIONCOMPONENT_H
