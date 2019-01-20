#include "transitioncomponent.h"

/**
 * @brief TransitionComponent::TransitionComponent
 * @param onFinished
 * @param transition
 * @param duration
 * @param autoplay
 */
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

/**
 * @brief TransitionComponent::render
 * @param painter
 */
void TransitionComponent::render(QPainter* painter)
{
    if(done) return;
    renderTransitionAnimation(painter, parent, duration, ticksPassed);
}

/**
 * @brief TransitionComponent::update
 */
void TransitionComponent::update()
{
    if(done) return;

    if(++ticksPassed > duration)
    {
        done = true;
        onFinished();
    }
}

/**
 * @brief TransitionComponent::restart
 */
void TransitionComponent::restart()
{
    ticksPassed = 0;
    done = false;
}
