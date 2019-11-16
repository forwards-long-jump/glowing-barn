#include "objectlayerentity.h"

/**
 * @brief ObjectLayerEntity::ObjectLayerEntity
 * @param objectGroup
 * @param renderer
 * @param parent
 * @param spawnName
 */
ObjectLayerEntity::ObjectLayerEntity(Tiled::ObjectGroup* objectGroup, Tiled::MapRenderer*, Entity* parent, QString spawnName, Game* game)
    : Entity(parent)
{
    setFlag(QGraphicsItem::ItemHasNoContents);
    setPos(objectGroup->offset());

    // Create a child item for each object
    for (Tiled::MapObject* object : objectGroup->objects())
    {
        switch (object->cell().tileId()) {
        case 240:
            EntityFactory::magnetZipper(object, this);
            break;
        case 248:
            if(object->propertyAsString("spawnName") == spawnName) {
                static_cast<MapEntity*>(parent)->setPlayer(EntityFactory::player(object, parent));
            }
            break;
        case 235:
            EntityFactory::box(object, this);
            break;
        case 236:
            // TODO: Grappling magnet
            break;
        case 237:
            EntityFactory::magnetJumper(object, this);
            break;
        case 238:
            EntityFactory::magnetGravity(object, this);
            break;
        default:
            if(object->name() == "graphic") {
                EntityFactory::graphic(object, parent);
            }
            else if(object->name() == "door") {
                EntityFactory::door(object, parent);
            }
            else if(object->name() == "button") {
                EntityFactory::gameButton(object, parent);
            }
            else if(object->name() == "spark") {
                EntityFactory::spark(object, parent);
            }
            else if(object->name() == "hurt") {
                EntityFactory::hurt(object, parent);
            }
            else if(object->name() == "invisible-wall") {
                EntityFactory::collision(object->position(), object->size(), parent);
            }
            else if(object->name() == "story-activation") {
                EntityFactory::storyActivation(object, parent);
            }
            else if(object->name() == "story-magnet") {
                EntityFactory::storyMagnet(object, parent);
            }
            else if(object->name() == "sound") {
                EntityFactory::soundButtonReactor(object, parent);
            }
            else if(object->name() == "camera") {
                EntityFactory::cameraSequence(object, parent);
            }
            else if(object->name() == "text") {
                EntityFactory::text(object, parent, game);
            }
            else {
                qWarning() << "unknown object " << object->name();
            }
            break;
        }
    }
}

/**
 * @brief ObjectLayerEntity::boundingRect
 * @return
 */
QRectF ObjectLayerEntity::boundingRect() const
{
    return QRectF();
}

/**
 * @brief ObjectLayerEntity::paint
 * @param painter
 * @param option
 * @param widget
 */
void ObjectLayerEntity::paint(QPainter* p, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Entity::paint(p, option, widget);
}
