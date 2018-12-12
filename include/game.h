#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMap>
#include <QTime>
#include <QTimer>

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

    static Input input;

signals:
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);

private:
    QMap<QString, QGraphicsScene *> scenes;
    QGraphicsScene *currentScene;

    const int MS_PER_UPDATE = 1000 / 60;
    QTimer *updateTimer;
    QTime *lastUpdateTime;
    int lag;

private slots:
    void update();

};

#endif // GAME_H
