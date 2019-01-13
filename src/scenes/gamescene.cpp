#include "gamescene.h"

GameScene::GameScene(QString name, Game* game)
    : Scene(name, game)
{
    changeMapScheduled = false;
    loadMap(":maps/map-outside-factory.tmx");

    // If a dev map is set, adds a file watcher to reload the map automatically every time it is changed on disk
    if(DEV_MAP_PATH != "") {
        mapReloadWatcher.addPath(DEV_MAP_PATH);
        connect(&mapReloadWatcher, &QFileSystemWatcher::fileChanged, this, [=] () {
            mapReloadWatcher.addPath(DEV_MAP_PATH);
            loadMap(DEV_MAP_PATH);
        });
    }
}

GameScene::~GameScene()
{

}

void GameScene::scheduleMapChange(QString mapPath, QString spawnName)
{
    if(mapPath != "")
    {
        newMapPath = mapPath;
        newMapSpawn = spawnName;
    }

    Sounds::fadeOut(20);

    Entity* e = new Entity(nullptr, -map->width() * 16, -map->height() * 16, map->width() * 32, map->height() * 32);

    e->addComponent(new TransitionComponent(
                [=]() {
                    changeMapScheduled = true;
                },
                [](QPainter* painter, const Entity* entity, int duration, int ticksPassed) {
                    painter->fillRect(0, 0, entity->getSize().width(), entity->getSize().height(),
                        QColor(0, 0, 0, 255 * static_cast<float>(ticksPassed) / duration));
                }, 20
    ));

    addItem(e);
}

Entity *GameScene::getPlayer() const
{
    return mapItem->getPlayer();
}

void GameScene::update()
{
    if(changeMapScheduled)
    {
        changeMapScheduled = false;
        loadMap(newMapPath, newMapSpawn);
    }

    if(Game::input.isKeyDown(Input::Key::PAUSE_MENU))
    {
        if(canPressPauseKey)
        {
            canPressPauseKey = false;
            game->togglePaused();
        }
    }
    else
    {
        canPressPauseKey = true;
    }
}

void GameScene::onKeyChange(Input &input)
{
    // Handle going back to main menu
    if(Game::input.isKeyDown(Input::Key::QUIT_GAME) && game->isPaused())
    {
        game->switchScene("menu");
    }
}

bool GameScene::loadMap(QString filename, QString spawnName)
{
    newMapPath = filename;
    newMapSpawn = spawnName;

    HitboxComponent::removeAll();
    clear();

    Tiled::MapReader reader;

    map = reader.readMap(filename);

    if (!map) {
        qWarning().noquote() << "Error:" << reader.errorString();
        return false;
    }

    Sounds::playMusic(map->propertyAsString("musicPath"));

    mapRenderer = new Tiled::OrthogonalRenderer(map);
    mapItem = new MapItem(map, mapRenderer, nullptr, spawnName);
    mapItem->getLayer("middle")->createCollisions();

    mapItem->getLayer("front")->setZValue(1);
    mapItem->getPlayer()->setZValue(0);
    mapItem->getLayer("back")->setZValue(-1);

    camera->setScaling(map->property("zoom").toFloat());
    camera->setBoundingRect(QRectF(0, 0, map->width() * 16, 16 * map->height()));

    if(this->views().size() > 0)
    {
        QPointF playerCenter(mapItem->getPlayer()->getSize().width() / 2.0, mapItem->getPlayer()->getSize().height() / 2.0);
        camera->centerOn(mapItem->getPlayer()->pos() + playerCenter, this->views()[0]->viewport()->size(), false);
    }

    camera->attachTo(mapItem->getPlayer());

    this->addItem(mapItem);

    // TODO: Add a component forcing entity to be displayed as UI element instead of hardcoding an random size here
    Entity* e = new Entity(nullptr, -map->width() * 16, -map->height() * 16, map->width() * 16 * 4, map->height() * 16 * 4);

    e->addComponent(new TransitionComponent(
                [=]() {},
                [](QPainter* painter, const Entity* entity, int duration, int ticksPassed) {
                    if(ticksPassed < 5)
                    {
                            painter->fillRect(0, 0, entity->getSize().width(), entity->getSize().height(), Qt::black);
                    }
                    else
                    {
                            painter->fillRect(0, 0, entity->getSize().width(), entity->getSize().height(),
                                QColor(0, 0, 0, 255 + 5 - 255 * static_cast<float>(ticksPassed) / duration));
                    }
                }, 20
    ));

     Entity* pauseMenu = new Entity(nullptr, -map->width() * 16, -map->height() * 16, map->width() * 16 * 4, map->height() * 16 * 4);
     pauseMenu->addComponent(new GUIItemComponent);
     pauseMenu->addComponent(new GenericRenderComponent(
                                [](QPainter* p, Entity* e, int tick) {
                                    if(static_cast<GameScene*>(e->scene())->getGame()->isPaused())
                                    {
                                        // Since it's not a real fullscreen overlay we render it a bit on the left in case the windows size is changed...
                                        p->fillRect(-100, -100, e->getSize().width(), e->getSize().height(), QColor(0, 0, 0, 200));

                                        p->setFont(QFont("Serif", 15));
                                        p->setPen(QColor(250, 250, 250));
                                        p->drawText(20, 50, "Game paused");
                                        p->setFont(QFont("Serif", 7));
                                        p->drawText(20, 80, "[Escape]");
                                        p->drawText(20, 100, "[Q]");
                                        p->drawText(20, 120, "[M]");
                                        p->drawText(100, 80, "- Unpause");
                                        p->drawText(100, 100, "- Go back to menu");
                                        p->drawText(100, 120, "- Toggle music");
                                    }
                                }
                            )
    );


    addItem(pauseMenu);
    addItem(e);

    return true;
}
