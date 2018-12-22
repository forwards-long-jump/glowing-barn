#include "include/doorcomponent.h"
#include <QMessageBox>

#include <QDebug>

void DoorComponent::action(Entity *target) const
{
    // TODO destroy current lever and load next one / credits
    qDebug() << "ACTION";
}
