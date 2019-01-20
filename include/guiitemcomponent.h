#ifndef GUIITEMCOMPONENT_CPP
#define GUIITEMCOMPONENT_CPP

#include "gamescene.h"
#include "component.h"

/**
 * Makes its entity stay in an absolute position on screen
 *
 * @authors Alexandre Bianchi, Pierre Bürki, Loïck Jeanneret
 */

class GUIItemComponent : public Component
{
public:
    GUIItemComponent();

    void update() override;
};

#endif // GUIITEMCOMPONENT_CPP
