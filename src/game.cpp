#include "game.h"

Game::Game(QWidget *parent)
    : QGraphicsView(parent)
{
    // Basic Scene
    MenuScene *menuScene = new MenuScene("menu", this);
    GameScene *gameScene = new GameScene("game", this);

    this->setFrameStyle(QFrame::NoFrame);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setRenderHint(QPainter::Antialiasing, false);
    this->resize( width(), height() );
    this->setOptimizationFlags(QGraphicsView::DontSavePainterState);
    this->setViewportUpdateMode( QGraphicsView::SmartViewportUpdate);
    this->setCacheMode(QGraphicsView::CacheBackground);
    this->setViewportUpdateMode( QGraphicsView::FullViewportUpdate);

    currentScene = gameScene;

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

Input Game::input;

Game::~Game()
{
    //qDeleteAll(scenes.begin(), scenes.end());
    //scenes.clear();
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

        static_cast<Scene*>(scene())->updateCamera();
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
