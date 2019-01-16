#ifndef GAMEBUTTON_H
#define GAMEBUTTON_H

#include "hitboxreactorcomponent.h"
#include "squarehitboxcomponent.h"
#include "interactivereactorcomponent.h"
#include "input.h"

class GameButtonComponent : public InteractiveReactorComponent
{
public:
    GameButtonComponent(QString buttonName, Input::Key key, bool stayPressed = false,
                        bool invertOnOff = false, int pressedDurationInTick = 1, bool isTogglable = false,
                        QString requiredButtonsToPress = "",  QString requiredButtonsToRelease = "", QString name = "GameButtonComponent"
                        );

    GameButtonComponent(QString buttonName, bool stayPressed = false,
                        bool invertOnOff = false, int pressedDurationInTick = 1, bool isTogglable = false,
                        QString requiredButtonsToPress = "",  QString requiredButtonsToRelease = "",
                        QString reactorName = GameButtonComponent::HITBOX_REACTOR_NAME, QString name = "GameButtonComponent");

    ~GameButtonComponent();

    const static QString HITBOX_REACTOR_NAME;
    const static QString HITBOX_NAME;
    static bool areButtonsPressed(QVector<QString> buttons);
    static QVector<QString> getButtonVectorFromString(QString buttons);

    bool isPressed();

    void init() override;
    void onDisable() override;
    void onEnable() override;
    void update() override;

    void action(Entity* target) override;

protected:
    static QVector<GameButtonComponent* > instances;

    QString buttonName;
    QVector<QString> requiredButtonsToPress;
    QVector<QString> requiredButtonsToRelease;
    bool stayPressed = false;
    bool invertOnOff = false;
    bool pressed = false;
    int pressedDurationInTick = 0;
    int pressedTicksLeft = 0;
    bool isTogglable = false;

    bool canBePressed();
    bool canBeReleased();
};

#endif // GAMEBUTTON_H
