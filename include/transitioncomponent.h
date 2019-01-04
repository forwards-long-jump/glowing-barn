#ifndef FADEOUTCOMPONENT_H
#define FADEOUTCOMPONENT_H

#include "graphicscomponent.h"

class TransitionComponent : public GraphicsComponent
{
public:
    TransitionComponent(std::function<void()> onFinished,
                        std::function<void(QPainter *, const Entity *, int, int)> renderTransitionAnimation,
                        int duration);

    void render(QPainter* painter) override;
    void update() override;

private:
    std::function<void()> onFinished;
    std::function<void(QPainter*, Entity* e, int duration, int ticksPassed)> renderTransitionAnimation;

    int duration = 0;
    int ticksPassed = 0;
    bool done = false;
};

#endif // FADEOUTCOMPONENT_H
