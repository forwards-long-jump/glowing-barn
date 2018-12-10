#include "../../include/magneticfieldreactorcomponent.h"

MagneticFieldReactorComponent::MagneticFieldReactorComponent()
{

}

void MagneticFieldReactorComponent::update()
{
    // TODO: for each HitboxComponent::getByName(ZipperMagnetComponent::HITBOX_NAME)
    //          handleZipperMagnet(HitboxComponent...);
    handleZipperMagnet();
}

void MagneticFieldReactorComponent::handleZipperMagnet(/*TODO: HitboxComponent &hitboxComponent*/)
{
    // TODO: Remove this debug line
    ZipperMagnetComponent *zipperMagnet = new ZipperMagnetComponent(ZipperMagnetComponent::DIRECTION::UP, QSizeF(-1, -1), 5);
    // TODO: zipperMagnet =  hitboxComponent.getEntity()->getComponent("ZipperMagnetComponent");
    if(true) // Is in hitbox
    {
        PhysicsComponent *p = dynamic_cast<PhysicsComponent*>(getEntity()->getComponent("PhysicsComponent"));
        if(p) {

            p->disableGravityForTick();
        }
        else {
            qDebug() << "Cannot get physicsComponent";
        }
        switch(zipperMagnet->getDirection())
        {
        case ZipperMagnetComponent::DIRECTION::DOWN:
            getEntity()->setPos(getEntity()->x(), getEntity()->y() + zipperMagnet->getSpeed());
            break;
        case ZipperMagnetComponent::DIRECTION::UP:
            getEntity()->setPos(getEntity()->x(), getEntity()->y() - zipperMagnet->getSpeed());
            break;
        case ZipperMagnetComponent::DIRECTION::LEFT:
            getEntity()->setPos(getEntity()->x() + zipperMagnet->getSpeed(), getEntity()->y());
            break;
        case ZipperMagnetComponent::DIRECTION::RIGHT:
            getEntity()->setPos(getEntity()->x() - zipperMagnet->getSpeed(), getEntity()->y());
            break;
        }
    }
    delete zipperMagnet;
}
