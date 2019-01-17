#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMap>
#include <QTime>
#include <QTimer>
#include <QGLWidget>

#include "gamescene.h"
#include "menuscene.h"
#include "creditsscene.h"
#include "input.h"
#include "sounds.h"

class GameScene;

/**
 * Main widget, core of the application
 *
 * @authors Alexandre Bianchi, Pierre Bürki, Loïck Jeanneret
 */

class Game : public QGraphicsView
{
    Q_OBJECT

public:
    Game(QWidget* parent = 0);
    ~Game();

    void addScene(QString nameScene, Scene* scene);
    void switchScene(QString nameScene);

    void addEntityLater(Entity* entityToAdd, Entity* parentEntity);

    unsigned int getTick() const;

    static Input input;

    void togglePaused();

    bool isPaused() const;

signals:
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);

private:
    // Prevent scrolling the view
    void scrollContentsBy(int, int) override {}

    QVector<QPair<Entity*, Entity*>> entitiesToAddLater;
    QMap<QString, Scene* > scenes;
    Scene* currentScene = nullptr;

    const int MS_PER_UPDATE = 1000 / 60;
    QTimer* updateTimer;
    QTime* lastUpdateTime;
    int lag;
    unsigned int tick;
    bool paused = false;
    bool canPressMuteKey = true;

    void handleToggleMute();
private slots:
    void update();

};

#endif // GAME_H
