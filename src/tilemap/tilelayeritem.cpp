#include "tilelayeritem.h"

TileLayerItem::TileLayerItem(Tiled::TileLayer *tileLayer, Tiled::MapRenderer *renderer, QGraphicsItem *parent)
    : Entity(parent)
    , mTileLayer(tileLayer)
    , mRenderer(renderer)
{
    setFlag(QGraphicsItem::ItemUsesExtendedStyleOption);
    setPos(mTileLayer->offset());
}

/**
 * @brief createCollisions
 * @return an entity vector of collisions
 */
QVector<Entity*> TileLayerItem::createCollisions() const
{
    QVector<Entity*> entities;
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
                Entity *entity = new Entity(nullptr, 16, 16 * heightTile);
                entity->setPos(posX*16, posY*16);
                entity->addComponent(new HitboxComponent("WallComponent"));

                entities.push_back(entity);

                posX = 0;
                posY = 0;
                heightTile = 0;
                firstTile = false;
            }
        }
    }

    return entities;
}

QRectF TileLayerItem::boundingRect() const
{
    return mRenderer->boundingRect(mTileLayer->bounds());
}

void TileLayerItem::paint(QPainter *p, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Entity::paint(p, option, widget);
    mRenderer->drawTileLayer(p, mTileLayer, option->rect);
}
