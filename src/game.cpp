#include "game.h"

Input Game::input;

Game::Game(QWidget* parent)
    : QGraphicsView(parent)
{
    QMediaPlayer* player = new QMediaPlayer(this, QMediaPlayer::LowLatency);
    Sounds::setMediaPlayer(player);
    Sounds::loadSounds();

    // Set OpenGL
    this->setViewport(new QGLWidget());

    // Basic Scene
    new MenuScene("menu", this);
    new GameScene("game", this);
    new CreditsScene("credits", this);

    this->setFrameStyle(QFrame::NoFrame);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setRenderHint(QPainter::Antialiasing, false);
    this->resize( width(), height() );
    this->setOptimizationFlags(QGraphicsView::DontSavePainterState);
    this->setViewportUpdateMode( QGraphicsView::SmartViewportUpdate);
    this->setCacheMode(QGraphicsView::CacheBackground);
    this->setViewportUpdateMode( QGraphicsView::FullViewportUpdate);

    this->switchScene("game");

    // Connections
    connect(this, &Game::keyPressEvent,
            [=](QKeyEvent* event)
                {
                    input.handleKeyDown(event);
                    static_cast<Scene*>(scene())->onKeyChange(input);
                }
            );
    connect(this, &Game::keyReleaseEvent,
            [=](QKeyEvent* event)
                {
                    input.handleKeyUp(event);
                    static_cast<Scene*>(scene())->onKeyChange(input);
                }
            );

    // Update "loop"
    lastUpdateTime = new QTime(QTime::currentTime());
    lag = 0;
    tick = 0;

    updateTimer = new QTimer(this);
    updateTimer->setInterval(MS_PER_UPDATE);

    connect(updateTimer, &QTimer::timeout, this, &Game::update);
    updateTimer->start();
}

Game::~Game()
{
    qDeleteAll(scenes);
    scenes.clear();
}

/**
 * @brief Game::update
 */
void Game::update() {
    // Add lag due to timer
    lag = lastUpdateTime->elapsed();
    tick++;

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
        static_cast<Scene*>(scene())->update();
        Sounds::update();

        lag -= MS_PER_UPDATE;
        lastUpdateTime->start();
    }
}

/**
 * @brief Game::addScene
 * @param nameScene
 * @param scene
 */
void Game::addScene(QString nameScene, Scene* scene)
{
    scenes.insert(nameScene, scene);
}

/**
 * @brief Game::switchScene
 * @param scene
 */
void Game::switchScene(QString nameScene)
{
    if(this->currentScene)
        currentScene->onLeave();

    this->currentScene = scenes[nameScene];
    if(this->currentScene)
        currentScene->onEnter();

    this->setScene(currentScene);
}

unsigned int Game::getTick() const
{
    return tick;
}
