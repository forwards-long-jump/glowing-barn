#include "gamescene.h"
#include "debugcomponent.h"
#include "playerinputcomponent.h"
#include "physicscomponent.h"
#include "magneticfieldreactorcomponent.h"

#include "debugcomponent.h"
#include "playerinputcomponent.h"
#include "physicscomponent.h"
#include "hitboxcomponent.h"
#include "animationcomponent.h"

#include "doorcomponent.h"

const QString DEV_MAP_PATH = "C:/Users/Lockj/Desktop/glowing-barn/assets/maps/map-test.tmx";

GameScene::GameScene(QString name, Game *game)
    : Scene(name, game)
{
    loadMap(":maps/map-test.tmx");

    Entity* door = new Entity(nullptr, 352, 48, 16, 32);
    addItem(door);
    door->addComponent(new DoorComponent());
    map = nullptr;
}

GameScene::~GameScene()
{

}

void GameScene::onKeyChange(Input &input)
{
    if(DEV_MAP_PATH != "" && input.isDebugKeyDown(Qt::Key_F11)) {
        if(mapReloadWatcher.files().length() == 0)
        {
            mapReloadWatcher.addPath(DEV_MAP_PATH);
            connect(&mapReloadWatcher, &QFileSystemWatcher::fileChanged, this, [=] () {
                loadMap(DEV_MAP_PATH);
            });
        }

        loadMap(DEV_MAP_PATH);
    }
}

bool GameScene::loadMap(QString filename)
{
    HitboxComponent::removeAll();
    clear();

    Tiled::MapReader reader;
    MapItem *mapItem;

    map = reader.readMap(filename);

    if (!map) {
        qWarning().noquote() << "Error:" << reader.errorString();
        return false;
    }

    mapRenderer = new Tiled::OrthogonalRenderer(map);
    mapItem = new MapItem(map, mapRenderer);
    mapItem->getLayer("middle")->createCollisions();

    mapItem->getLayer("front")->setZValue(1);
    mapItem->getPlayer()->setZValue(0);
    mapItem->getLayer("back")->setZValue(-1);
    QVector<QPair<QString, QVector<float>>> animations;
    AnimationComponent::addAnimationToVector("running", 8, 5, animations);
    AnimationComponent::addAnimationToVector("standing", 2, 15, animations);
    AnimationComponent::addAnimationToVector("skidding", 1, 1, animations);
    AnimationComponent::addAnimationToVector("jumping", 1, 1, animations);
    AnimationComponent::addAnimationToVector("zipping", 3, 10, animations);
    mapItem->getPlayer()->addComponent(new AnimationComponent("/entities/player.png", 16, animations));

    camera->attachTo(mapItem->getPlayer());
    camera->setScaling(6);
    camera->setBoundingRect(QRectF(0, 0, map->width() * 16, 16 * map->height()));

    this->addItem(mapItem);

    return true;
}
