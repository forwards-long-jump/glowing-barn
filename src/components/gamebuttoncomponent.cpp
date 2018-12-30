#include "gamebuttoncomponent.h"

QVector<GameButtonComponent *> GameButtonComponent::instances;
const QString GameButtonComponent::HITBOX_REACTOR_NAME = "GameButtonPresser";

GameButtonComponent::GameButtonComponent(QString buttonName, QString name) : HitboxReactorComponent(HITBOX_REACTOR_NAME, name)
{
    buttonName = name;
    instances.append(this);
}

GameButtonComponent::~GameButtonComponent()
{
    instances.removeOne(this);
}

/**
 * @brief Returns if this button is pressed or not
 * @return
 */
bool GameButtonComponent::isPressed()
{
    return pressed;
}

/**
 * @brief Check if all given buttons are pressed
 * @param buttons
 * @return
 */
bool GameButtonComponent::areButtonsPressed(QVector<QString> buttons)
{
    int matchCount = 0;
    int matchRequired = buttons.size();

    for(GameButtonComponent* b : instances)
    {
        for(int i = 0; i < buttons.size(); ++i)
        {
            if(buttons[i] == b->buttonName && b->isPressed())
            {
                matchCount++;

                if(matchCount >= matchRequired)
                {
                    return true;
                }

                break;
            }
        }
    }

    return false;
}

void GameButtonComponent::init()
{
    setHitbox(new SquareHitboxComponent());
}

void GameButtonComponent::onDisable()
{
    instances.removeOne(this);
}

void GameButtonComponent::onEnable()
{
    instances.append(this);
}

void GameButtonComponent::onIntersect(HitboxComponent *hb)
{
    qDebug() << "Pressed button";
}
