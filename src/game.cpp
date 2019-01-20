#include "game.h"

Input Game::input;

/**
 * @brief Game::Game
 * @param parent
 */
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

    this->switchScene("menu");

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

/**
 * @brief Game::~Game
 */
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

    while(lag > MS_PER_UPDATE)
    {
        tick++;

        if(!paused)
        {
            for(int i = 0; i < items().length(); ++i)
            {
                Entity* entity = static_cast<Entity*>(items()[i]);
                if(entity->shouldBeDeleted())
                {
                    delete items()[i];
                    i--;
                }
                else
                {
                    entity->update();
                }
            }


            if(entitiesToAddLater.length())
            {
                for(int i = 0; i < entitiesToAddLater.length(); ++i)
                {
                    entitiesToAddLater[i].first->setParentItem(entitiesToAddLater[i].second);
                }
                entitiesToAddLater.clear();
            }

            static_cast<Scene*>(scene())->updateCamera();
        }

        static_cast<Scene*>(scene())->update();
        Sounds::update();
        handleToggleMute();

        lag -= MS_PER_UPDATE;
        lastUpdateTime->start();
    }
}

/**
 * @brief Game::handleToggleMute
 */
void Game::handleToggleMute()
{
    if(input.isKeyDown(Input::Key::MUTE_GAME))
    {
        if(canPressMuteKey)
        {
            canPressMuteKey = false;
            Sounds::toggleMute();
        }
    }
    else
    {
        canPressMuteKey = true;
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

/**
 * @brief Game::addEntityLater
 * @param entityToAdd
 * @param parentEntity
 */
void Game::addEntityLater(Entity *entityToAdd, Entity *parentEntity)
{
    entitiesToAddLater.append(QPair<Entity*, Entity*>(entityToAdd, parentEntity));
}

/**
 * @brief Game::getTick
 * @return
 */
unsigned int Game::getTick() const
{
    return tick;
}

/**
 * @brief Game::togglePaused
 */
void Game::togglePaused()
{
    paused = !paused;
}

/**
 * @brief Game::isPaused
 * @return
 */
bool Game::isPaused() const
{
    return paused;
}
