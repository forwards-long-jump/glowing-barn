#ifndef GUIITEMCOMPONENT_CPP
#define GUIITEMCOMPONENT_CPP

#include "gamescene.h"
#include "component.h"

class GUIItemComponent : public Component
{
public:
    GUIItemComponent();

    void update() override;
};

#endif // GUIITEMCOMPONENT_CPP
