#include "tilelayerentity.h"

/**
 * @brief TileLayerEntity::TileLayerEntity
 * @param tileLayer
 * @param renderer
 * @param parent
 */
TileLayerEntity::TileLayerEntity(Tiled::TileLayer* tileLayer, Tiled::MapRenderer* renderer, Entity* parent)
    : Entity(parent),
      tileLayer(tileLayer),
      renderer(renderer)
{
    setFlag(QGraphicsItem::ItemUsesExtendedStyleOption);
    setPos(tileLayer->offset());
}

/**
 * @brief createCollisions
 * @return an entity vector of collisions
 */
void TileLayerEntity::createCollisions()
{
    QVector<Entity*> collisions;
    int width = tileLayer->width();
    int height = tileLayer->height();

    for(int x = 0; x < width; x++)
    {
        bool firstTile = false;
        int posX = 0;
        int posY = 0;
        int heightTile = 0;

        for(int y = 0; y < height; y++)
        {
            Tiled::Cell cell = tileLayer->cellAt(x, y);

            if(cell.tileId() != -1 && y != height - 1 )
            {
                if(!firstTile)
                {
                    posX = x;
                    posY = y;
                    firstTile = true;
                }
                heightTile++;
            }
            else if (heightTile > 0 || (y == height - 1 && cell.tileId() != -1))
            {
                // For specific case
                // If the cell is the last one and alone
                if(heightTile == 0)
                {
                    posX = x;
                    posY = y;
                }
                // To create the last height of the collision
                if(y == height - 1 && cell.tileId() != -1)
                    heightTile++;

                // Create the entity for the collision
                Entity* entity = EntityFactory::collision(QPointF(posX*16, posY*16), QSizeF(16, 16 * heightTile), this);
                collisions.push_back(entity);

                posX = 0;
                posY = 0;
                heightTile = 0;
                firstTile = false;
            }
        }
    }
}

/**
 * @brief TileLayerEntity::boundingRect
 * @return
 */
QRectF TileLayerEntity::boundingRect() const
{
    return renderer->boundingRect(tileLayer->bounds());
}

/**
 * @brief TileLayerEntity::paint
 * @param painter
 * @param option
 * @param widget
 */
void TileLayerEntity::paint(QPainter* p, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Entity::paint(p, option, widget);
    renderer->drawTileLayer(p, tileLayer, option->rect);
}
