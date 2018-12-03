#include "include/input.h"

Input::Input()
{

}

bool Input::isKeyDown(int key)
{
    if (keys.contains(key))
    {
        return keys.value(key);
    }
    else
    {
        return false;
    }
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
