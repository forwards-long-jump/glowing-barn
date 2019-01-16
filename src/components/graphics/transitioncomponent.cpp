#include "transitioncomponent.h"

TransitionComponent::TransitionComponent(std::function<void()> onFinished,
                                         std::function<void(QPainter* , const Entity* , int, int)> transition,
                                         int duration, bool autoplay)
    : GraphicsComponent("TransitionComponent"),
      onFinished(onFinished),
      renderTransitionAnimation(transition),
      duration(duration)
{
    done = !autoplay;
}

void TransitionComponent::render(QPainter* painter)
{
    if(done) return;
    renderTransitionAnimation(painter, parent, duration, ticksPassed);
}

void TransitionComponent::update()
{
    if(done) return;

    if(++ticksPassed > duration)
    {
        done = true;
        onFinished();
    }
}

void TransitionComponent::restart()
{
    ticksPassed = 0;
    done = false;
}
