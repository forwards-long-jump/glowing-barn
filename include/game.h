#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMap>

#include <gamescene.h>
#include <menuscene.h>

class GameScene;

class Game : public QGraphicsView
{
    Q_OBJECT

public:
    Game(QWidget *parent = 0);
    ~Game();

    void addScene(QString nameScene, QGraphicsScene *scene);
    void switchScene(QString nameScene);

private:
    QMap<QString, QGraphicsScene *> scenes;
    QGraphicsScene *currentScene;

};

#endif // GAME_H
