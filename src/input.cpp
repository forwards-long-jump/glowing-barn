#include "input.h"

Input::Input()
{
    bindings[LEFT]      = Qt::Key_Left;
    bindings[RIGHT]     = Qt::Key_Right;
    bindings[JUMP]      = Qt::Key_Up;
    bindings[INTERACT]  = Qt::Key_Down;
    bindings[ZIP]       = Qt::Key_Space;
    bindings[PAUSE_MENU]    = Qt::Key_Escape;
    bindings[MUTE_GAME] = Qt::Key_M;
    bindings[QUIT_GAME] = Qt::Key_Q;
}

bool Input::isDebugKeyDown(Qt::Key key)
{
    return keys.value(key, false);
}

bool Input::isKeyDown(Key key)
{
    return key == Input::Key::NONE || keys.value(bindings[key], false);
}

void Input::handleKeyDown(QKeyEvent* event)
{
    int key = event->key();
    keys.insert(key, true);
}

void Input::handleKeyUp(QKeyEvent* event)
{
    int key = event->key();
    keys.insert(key, false);
}
