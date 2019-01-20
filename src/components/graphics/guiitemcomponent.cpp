#include "guiitemcomponent.h"

/**
 * @brief GUIItemComponent::GUIItemComponent
 */
GUIItemComponent::GUIItemComponent()
    : Component("GUIItemComponent")
{

}

/**
 * @brief GUIItemComponent::update
 */
void GUIItemComponent::update()
{
    Camera* c = static_cast<GameScene*>(getParent()->scene())->getCamera();
    getParent()->setPos(c->getPosition() + c->getCameraForce());
}
