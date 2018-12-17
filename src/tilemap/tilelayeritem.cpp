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

    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            Tiled::Cell cell = mTileLayer->cellAt(x, y);

            if(cell.tileId() != -1)
            {
                Entity *entity = new Entity(nullptr, 16, 16);
                entity->setPos(x*16, y*16);
                //entity->addComponent(new DebugComponent());
                entity->addComponent(new HitboxComponent("WallComponent"));

                entities.push_back(entity);
            }
        }
    }

    return entities;
}

/**
 * @brief TileLayerItem::findBoundsRect
 * @param start_y
 * @param start_x
 * @param end_x
 * @param checked
 * @return
 */
QRect TileLayerItem::findBoundsRect(int start_y, int start_x, int end_x, QVector<bool> *checked) const
{
    int index = -1;
    int tileID = -1;
    int width = mTileLayer->width();
    int height = mTileLayer->height();

    for(int y = start_y + 1; y < height; y++)
    {
        for(int x = start_x; x < end_x; x++)
        {

            index = y * width + x;

            tileID =  mTileLayer->cellAt(x, y).tileId();

            if(tileID == 0 || (*checked)[index] == true){

                //Set everything we've visited so far in this row to false again because it won't be included in the rectangle and should be checked again
                for(int _x = start_x; _x < x; _x++) {
                    index = y * width + _x;
                    (*checked)[index] = false;
                }

                return QRect(start_x, start_y, end_x - start_x, y - start_y);

            }

            (*checked)[index] = true;

        } //each x
    } //each y

    return QRect(start_x, start_y, end_x - start_x, height - start_y);

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
