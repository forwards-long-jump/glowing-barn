#include "input.h"

/**
 * @brief Input::Input
 */
Input::Input()
{
    bindings[LEFT]       = Qt::Key_Left;
    bindings[RIGHT]      = Qt::Key_Right;
    bindings[JUMP]       = Qt::Key_Up;
    bindings[INTERACT]   = Qt::Key_Down;
    bindings[ZIP]        = Qt::Key_Space;
    bindings[PAUSE_MENU] = Qt::Key_Escape;
    bindings[START_GAME] = Qt::Key_Enter;
    bindings[START_GAME2] = Qt::Key_Return;
    bindings[MUTE_GAME]  = Qt::Key_M;
    bindings[QUIT_GAME]  = Qt::Key_Q;
}

/**
 * @brief Input::isDebugKeyDown
 * @param key
 * @return
 */
bool Input::isDebugKeyDown(Qt::Key key)
{
    return keys.value(key, false);
}

/**
 * @brief Input::isKeyDown
 * @param key
 * @return
 */
bool Input::isKeyDown(Key key)
{
    return key == Input::Key::NONE || keys.value(bindings[key], false);
}

/**
 * @brief Input::handleKeyDown
 * @param event
 */
void Input::handleKeyDown(QKeyEvent* event)
{
    int key = event->key();
    keys.insert(key, true);
}

/**
 * @brief Input::handleKeyUp
 * @param event
 */
void Input::handleKeyUp(QKeyEvent* event)
{
    int key = event->key();
    keys.insert(key, false);
}
