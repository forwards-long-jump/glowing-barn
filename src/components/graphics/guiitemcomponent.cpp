#include "guiitemcomponent.h"

GUIItemComponent::GUIItemComponent()
{

}

void GUIItemComponent::update()
{
    Camera* c = static_cast<GameScene*>(getParent()->scene())->getCamera();
    getParent()->setPos(c->getPosition() + c->getCameraForce());
}
