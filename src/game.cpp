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
}

Game::~Game()
{
    qDeleteAll(scenes.begin(), scenes.end());
    scenes.clear();
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
