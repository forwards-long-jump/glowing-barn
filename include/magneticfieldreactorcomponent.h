#ifndef MAGNETREACTORCOMPONENT_H
#define MAGNETREACTORCOMPONENT_H

#include "component.h"
#include "zippermagnetcomponent.h"
#include "physicscomponent.h"

class MagneticFieldReactorComponent : public Component
{
public:
    MagneticFieldReactorComponent();
    void update() override;
private:
    void handleZipperMagnet(/*TODO: HitboxComponent &hitboxComponent*/);

};

#endif // MAGNETREACTORCOMPONENT_H
