#ifndef GAMEBUTTON_H
#define GAMEBUTTON_H

#include "hitboxreactorcomponent.h"
#include "squarehitboxcomponent.h"
#include "interactivecomponent.h"
#include "input.h"

class GameButtonComponent : public InteractiveComponent
{
public:
    GameButtonComponent(QString buttonName, Input::Key key, bool stayPressed = false,
                        bool invertOnOff = false, int pressedDurationInTick = 1, bool isTogglable = false, QString name = "GameButtonComponent");
    GameButtonComponent(QString buttonName, bool stayPressed = false, bool invertOnOff = false,
                        int pressedDurationInTick = 1, bool isTogglable = false, QString name = "GameButtonComponent");
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

private:
    static QVector<GameButtonComponent *> instances;

    QString buttonName;
    bool stayPressed;
    bool invertOnOff;
    bool pressed;
    int pressedDurationInTick;
    int pressedTicksLeft;
    bool isTogglable;
};

#endif // GAMEBUTTON_H
