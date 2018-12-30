#ifndef GAMEBUTTON_H
#define GAMEBUTTON_H

#include "hitboxreactorcomponent.h"
#include "squarehitboxcomponent.h"
#include <QDebug>

class GameButtonComponent : public HitboxReactorComponent
{
public:
    const static QString HITBOX_REACTOR_NAME;
    const static QString HITBOX_NAME;
     static bool areButtonsPressed(QVector<QString> buttons);

    GameButtonComponent(QString buttonName, QString name = "GameButtonComponent");
    ~GameButtonComponent();

    bool isPressed();

    void init() override;
    void onDisable() override;
    void onEnable() override;
    void onIntersect(HitboxComponent* hb) override;


private:
    static QVector<GameButtonComponent *> instances;

    QString buttonName;
    bool pressed;
    // invertOnOff
    // stayPressed
    // requiresKey? // => InteractiveHBC
    // TODO: TEST BY USING INTERACTIVE COMPONENT FIRST, make the tooltip optionnal and check if can still use onIntersect

};

#endif // GAMEBUTTON_H
