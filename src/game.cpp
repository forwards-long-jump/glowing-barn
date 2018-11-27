#include "game.h"

Game::Game(QWidget *parent)
    : QGraphicsView(parent)
{
    // Basic Scene
    MenuScene *menuScene = new MenuScene("menu", this);
    GameScene *gameScene = new GameScene("game", this);

    currentScene = menuScene;

    this->setScene(currentScene);

    // Connections
    connect(this, &Game::keyPressEvent,
            [=](QKeyEvent* event) {input.handleKeyDown(event);}
            );
    connect(this, &Game::keyReleaseEvent,
            [=](QKeyEvent* event) {input.handleKeyUp(event);}
            );

    // Update "loop"
    lastUpdateTime = new QTime(QTime::currentTime());
    lag = 0;

    updateTimer = new QTimer(this);
    updateTimer->setInterval(MS_PER_UPDATE);

    connect(updateTimer, &QTimer::timeout, this, &Game::update);
    updateTimer->start();
}

Game::~Game()
{
    qDeleteAll(scenes.begin(), scenes.end());
    scenes.clear();
}

/**
 * @brief Game::update
 */
void Game::update() {
    // Add lag due to timer
    lag = lastUpdateTime->elapsed();

    while(lag > MS_PER_UPDATE) {
        // Make sure to only update Entities
        for(auto e : items()) {
            Entity* entity = dynamic_cast<Entity*>(e);
            if (entity)
            {
                entity->update();
            }
        }
        lag -= MS_PER_UPDATE;
        lastUpdateTime->start();
    }
}

/**
 * @brief Game::addScene
 * @param nameScene
 * @param scene
 */
void Game::addScene(QString nameScene, QGraphicsScene *scene)
{
    scenes.insert(nameScene, scene);
}

/**
 * @brief Game::switchScene
 * @param scene
 */
void Game::switchScene(QString nameScene)
{
    this->currentScene = scenes[nameScene];
    this->setScene(currentScene);
}
