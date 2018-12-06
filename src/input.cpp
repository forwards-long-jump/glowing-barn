#include "include/input.h"

Input::Input()
{
    bindings[LEFT]  = Qt::Key_Left;
    bindings[RIGHT] = Qt::Key_Right;
    bindings[JUMP]  = Qt::Key_Up;
    bindings[ZIP]   = Qt::Key_Space;
}

bool Input::isKeyDown(Key key)
{
    return keys.value(bindings[key], false);
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
