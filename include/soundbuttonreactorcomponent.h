#ifndef SOUNDBUTTONREACTORCOMPONENT_H
#define SOUNDBUTTONREACTORCOMPONENT_H

#include "component.h"
#include "sounds.h"

/**
 * Plays sounds depending on the state of its associated buttons
 *
 * @authors Alexandre Bianchi, Pierre Bürki, Loïck Jeanneret
 */

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

#include "gamebuttoncomponent.h"

#endif // SOUNDBUTTONREACTORCOMPONENT_H
