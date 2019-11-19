#include "input.h"

/**
 * @brief Input::Input
 */
Input::Input()
{
    bindings[LEFT]       = {Qt::Key_Left, Qt::Key_A};
    bindings[RIGHT]      = {Qt::Key_Right, Qt::Key_D};
    bindings[JUMP]       = {Qt::Key_Up, Qt::Key_W, Qt::Key_Space};
    bindings[INTERACT]   = {Qt::Key_Down, Qt::Key_S, Qt::Key_F};
    bindings[ZIP]        = {Qt::Key_Shift};
    bindings[PAUSE_MENU] = {Qt::Key_Escape};
    bindings[START_GAME] = {Qt::Key_Enter, Qt::Key_Return, Qt::Key_Space};
    bindings[MUTE_GAME]  = {Qt::Key_M};
    bindings[QUIT_GAME]  = {Qt::Key_Q};
    bindings[LOAD_LEVEL] = {Qt::Key_F8};
    bindings[RELOAD_LEVEL] = {Qt::Key_F5};
    bindings[LEVEL_SELECT] = {Qt::Key_Home};
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

void Input::setKeyDown(Key key)
{
    for(int qtKey : bindings[key]) {
        keys.insert(qtKey, false);
    }
}

/**
 * @brief Input::isKeyDown
 * @param key
 * @return
 */
bool Input::isKeyDown(Key key)
{
    for(int qtKey : bindings[key]) {
        if(keys.value(qtKey, false)) {
            return true;
        }
    }

    return key == Input::Key::NONE;
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
