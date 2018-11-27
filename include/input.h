#ifndef INPUT_H
#define INPUT_H

#include <QHash>
#include <QString>
#include <QKeyEvent>

class Input
{
public:
    Input();

    bool isKeyDown(int key);

public slots:
    void handleKeyDown(QKeyEvent* event);
    void handleKeyUp(QKeyEvent* event);

private:
    QHash<int, bool> keys;
};

#endif // INPUT_H
