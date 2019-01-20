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
    : InteractiveReactorComponent(key, name),
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
    : InteractiveReactorComponent(Input::Key::NONE, name, reactorName),
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
 * @brief GameButtonComponent::~GameButtonComponent
 */
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

/**
 * @brief GameButtonComponent::getButtonVectorFromString
 * @param buttons
 * @return
 */
QVector<QString> GameButtonComponent::getButtonVectorFromString(QString buttons)
{
    return buttons.split(" ", QString::SkipEmptyParts).toVector();
}

/**
 * @brief GameButtonComponent::init
 */
void GameButtonComponent::init()
{
    InteractiveReactorComponent::init();
    setHitbox(new SquareHitboxComponent());
}

/**
 * @brief GameButtonComponent::onDisable
 */
void GameButtonComponent::onDisable()
{
    instances.removeOne(this);
}

/**
 * @brief GameButtonComponent::onEnable
 */
void GameButtonComponent::onEnable()
{
    instances.append(this);
}

/**
 * @brief GameButtonComponent::update
 */
void GameButtonComponent::update()
{
    InteractiveReactorComponent::update();
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

/**
 * @brief GameButtonComponent::action
 * @param target
 */
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

/**
 * @brief GameButtonComponent::canBePressed
 * @return
 */
bool GameButtonComponent::canBePressed()
{
    if(requiredButtonsToPress.length() > 0)
    {
        return GameButtonComponent::areButtonsPressed(requiredButtonsToPress);
    }
    return true;
}

/**
 * @brief GameButtonComponent::canBeReleased
 * @return
 */
bool GameButtonComponent::canBeReleased()
{
    if(requiredButtonsToRelease.length() > 0)
    {
        return GameButtonComponent::areButtonsPressed(requiredButtonsToRelease);
    }
    return true;
}
