#ifndef INPUT_H
#define INPUT_H

#include <QHash>
#include <QString>
#include <QKeyEvent>

class Input
{
public:
    Input();

    enum Key
    {
        LEFT,
        RIGHT,
        JUMP,
        INTERACT,
        ZIP
    };

    bool isKeyDown(Key key);
    bool isDebugKeyDown(Qt::Key key);

public slots:
    void handleKeyDown(QKeyEvent* event);
    void handleKeyUp(QKeyEvent* event);

private:
    QHash<int, bool> keys;
    QHash<Key, int> bindings;
};

#endif // INPUT_H
