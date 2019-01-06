#ifndef SOUNDBUTTONREACTORCOMPONENT_H
#define SOUNDBUTTONREACTORCOMPONENT_H

#include "component.h"
#include "gamebuttoncomponent.h"
#include "sounds.h"

class SoundButtonReactorComponent : public Component
{
public:
    SoundButtonReactorComponent(QString startSound, QString endSound, QString idleSound, QString activeSound,
                                QString requiredButtons, QString name = "SoundButtonReactorComponent");
    void update() override;

private:
    enum SoundButtonState {
        IDLE,
        START,
        ACTIVE,
        END
    };

    QString startSound = "";
    QString endSound = "";
    QString idleSound = "";
    QString activeSound = "";

    QVector<QString> requiredButtons;
    SoundButtonState currentState = SoundButtonState::IDLE;
};

#endif // SOUNDBUTTONREACTORCOMPONENT_H
