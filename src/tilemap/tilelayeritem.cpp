#include "tilelayeritem.h"

/**
 * @brief TileLayerItem::TileLayerItem
 * @param tileLayer
 * @param renderer
 * @param parent
 */
TileLayerItem::TileLayerItem(Tiled::TileLayer* tileLayer, Tiled::MapRenderer* renderer, MapItem* parent)
    : Entity(parent),
      mTileLayer(tileLayer),
      mRenderer(renderer)
{
    setFlag(QGraphicsItem::ItemUsesExtendedStyleOption);
    setPos(mTileLayer->offset());
}

/**
 * @brief createCollisions
 * @return an entity vector of collisions
 */
void TileLayerItem::createCollisions()
{
    QVector<Entity*> collisions;
    int width = mTileLayer->width();
    int height = mTileLayer->height();

    for(int x = 0; x < width; x++)
    {
        bool firstTile = false;
        int posX = 0;
        int posY = 0;
        int heightTile = 0;

        for(int y = 0; y < height; y++)
        {
            Tiled::Cell cell = mTileLayer->cellAt(x, y);

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
 * @brief TileLayerItem::boundingRect
 * @return
 */
QRectF TileLayerItem::boundingRect() const
{
    return mRenderer->boundingRect(mTileLayer->bounds());
}

/**
 * @brief TileLayerItem::paint
 * @param painter
 * @param option
 * @param widget
 */
void TileLayerItem::paint(QPainter* p, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Entity::paint(p, option, widget);
    mRenderer->drawTileLayer(p, mTileLayer, option->rect);
}
