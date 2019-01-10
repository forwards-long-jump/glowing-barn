#include "game.h"

Game::Game(QWidget* parent)
    : QGraphicsView(parent)
{
    QMediaPlayer* player = new QMediaPlayer(this, QMediaPlayer::LowLatency);
    Sounds::setMediaPlayer(player);
    Sounds::loadSounds();

    // Set OpenGL
    this->setViewport(new QGLWidget());

    // Basic Scene
    MenuScene* menuScene = new MenuScene("menu", this);
    GameScene* gameScene = new GameScene("game", this);

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

    while(lag > MS_PER_UPDATE)
    {
        tick++;

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
void Game::addScene(QString nameScene, QGraphicsScene* scene)
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

void Game::addEntityLater(Entity *entityToAdd, Entity *parentEntity)
{
    entitiesToAddLater.append(QPair<Entity*, Entity*>(entityToAdd, parentEntity));
}

unsigned int Game::getTick() const
{
    return tick;
}
