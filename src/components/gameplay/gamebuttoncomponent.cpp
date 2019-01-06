#include "gamebuttoncomponent.h"

QVector<GameButtonComponent* > GameButtonComponent::instances;
const QString GameButtonComponent::HITBOX_REACTOR_NAME = "GameButtonPresser";

/**
 * @brief GameButtonComponent::GameButtonComponent
 * WARNING: This one will only work if the intersecting HitboxName is "InteractiveHitboxComponent" and is an IHC!
 * @param buttonName
 * @param key
 * @param name
 */
GameButtonComponent::GameButtonComponent(QString buttonName_, Input::Key key, bool stayPressed_,
                                         bool invertOnOff_, int pressedDurationInTick_, bool isTogglable_, QString requiredButtonsToPress_, QString requiredButtonsToRelease_, QString name)
    : InteractiveComponent(key, name),
      buttonName(buttonName_),
      stayPressed(stayPressed_),
      invertOnOff(invertOnOff_),
      pressedDurationInTick(pressedDurationInTick_),
      isTogglable(isTogglable_)
{
    requiredButtonsToPress = GameButtonComponent::getButtonVectorFromString(requiredButtonsToPress_);
    requiredButtonsToRelease = GameButtonComponent::getButtonVectorFromString(requiredButtonsToRelease_);
    instances.append(this);
}

/**
 * @brief GameButtonComponent::GameButtonComponent
 * This constructor allows any Hitbox named "GameButtonPresser" to trigger the button
 * @param buttonName
 * @param name
 */
GameButtonComponent::GameButtonComponent(QString buttonName_, bool stayPressed_,
                                         bool invertOnOff_, int pressedDurationInTick_, bool isTogglable_, QString requiredButtonsToPress_, QString requiredButtonsToRelease_, QString reactorName, QString name)
    : InteractiveComponent(Input::Key::NONE, name, reactorName),
      buttonName(buttonName_),
      stayPressed(stayPressed_),
      invertOnOff(invertOnOff_),
      pressedDurationInTick(pressedDurationInTick_),
      isTogglable(isTogglable_)
{
    requiredButtonsToPress = GameButtonComponent::getButtonVectorFromString(requiredButtonsToPress_);
    requiredButtonsToRelease = GameButtonComponent::getButtonVectorFromString(requiredButtonsToRelease_);
    instances.append(this);
}


//
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
    return pressed == !invertOnOff;
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
            bool buttonMustBePressed = true;
            QString buttonName = buttons[i];

            // Allows to invert the button required state by adding a ! in front of the button name
            if(buttonName[0] == '!')
            {
                buttonMustBePressed = false;
                buttonName = buttons[i].mid(1);
            }

            if(buttonName == b->buttonName && b->isPressed() == buttonMustBePressed)
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

QVector<QString> GameButtonComponent::getButtonVectorFromString(QString buttons)
{
    return buttons.split(" ", QString::SkipEmptyParts).toVector();
}

void GameButtonComponent::init()
{
    InteractiveComponent::init();
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

void GameButtonComponent::update()
{
    InteractiveComponent::update();
    if(pressedTicksLeft > 0)
    {
        pressedTicksLeft--;
    }
    else
    {
        if(!stayPressed && !isTogglable && canBeReleased())
        {
            pressed = false;
        }
    }
}

void GameButtonComponent::action(Entity* target)
{
    if(isTogglable)
    {
        if(pressed && canBeReleased())
        {
            pressed = false;
        }
        else if(!pressed && canBePressed())
        {
            pressed = true;
        }
    }
    else
    {
        if(canBePressed())
        {
            pressed = true;
            pressedTicksLeft = pressedDurationInTick;
        }
    }
}

bool GameButtonComponent::canBePressed()
{
    if(requiredButtonsToPress.length() > 0)
    {
        return GameButtonComponent::areButtonsPressed(requiredButtonsToPress);
    }
    return true;
}

bool GameButtonComponent::canBeReleased()
{
    if(requiredButtonsToRelease.length() > 0)
    {
        return GameButtonComponent::areButtonsPressed(requiredButtonsToRelease);
    }
    return true;
}
