#ifndef INPUT_H
#define INPUT_H

#include <QHash>
#include <QString>
#include <QKeyEvent>

/**
 * Keeps an updated list of pressed keys, to be read by others classes
 *
 * @authors Alexandre Bianchi, Pierre Bürki, Loïck Jeanneret
 */

class Input
{
public:
    Input();

    enum Key
    {
        NONE,
        LEFT, // left, a
        RIGHT, // right, d
        JUMP, // up, w, space
        INTERACT, // down, f, s
        ZIP, // shift
        PAUSE_MENU, // esc
        START_GAME, // enter, return, space
        MUTE_GAME, // m
        QUIT_GAME, // q
        LOAD_LEVEL, // f4
        RELOAD_LEVEL, // f5
        LEVEL_SELECT, // home
        CHANGE_LANGUAGE // f2
    };

    bool isKeyDown(Key key);
    bool isDebugKeyDown(Qt::Key key);
    void setKeyDown(Key key);

public slots:
    void handleKeyDown(QKeyEvent* event);
    void handleKeyUp(QKeyEvent* event);

private:
    QHash<int, bool> keys;
    QHash<Key, QList<int>> bindings;
};

#endif // INPUT_H
