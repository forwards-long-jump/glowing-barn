#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMap>

#include <gamescene.h>
#include <menuscene.h>
#include <input.h>

class GameScene;

class Game : public QGraphicsView
{
    Q_OBJECT

public:
    Game(QWidget *parent = 0);
    ~Game();

    void addScene(QString nameScene, QGraphicsScene *scene);
    void switchScene(QString nameScene);

    bool isKeyDown(int key) {return input.isKeyDown(key);}

signals:
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);

private:
    QMap<QString, QGraphicsScene *> scenes;
    QGraphicsScene *currentScene;

    Input input;
};

#endif // GAME_H
