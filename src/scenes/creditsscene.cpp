#include "creditsscene.h"

CreditsScene::CreditsScene(QString name, Game *game) : Scene(name, game)
{
    //Black background for fading
    this->setBackgroundBrush(Qt::black);

    bottom1 = new Entity(nullptr, 0, 32, 512, 48);
    bottom1->addComponent(new ImageComponent(":/credits/background.png"));
    bottom2 = new Entity(nullptr, -512, 32, 512, 48);
    bottom2->addComponent(new ImageComponent(":/credits/background.png"));
    credits = new Entity(nullptr, -103.5, 130, 223, 607);
    credits->addComponent(new ImageComponent(":/credits/credits.png"));
    thanks = new Entity(nullptr, -103.5, 882, 223, 31);
    thanks->addComponent(new ImageComponent(":/credits/thanks.png"));

    Entity* sky = new Entity(nullptr, -200, -200, 900, 300);
    sky->addComponent(new ImageComponent(":/decorations/sky.png"));
    sky->addComponent(new ParallaxComponent(1));
    mountains = new Entity(nullptr, -200, -64, 600, 96);
    mountains->addComponent(new ImageComponent(":/decorations/mountains.png"));
    bushes = new Entity(nullptr, -200, -46, 600, 96);
    bushes->addComponent(new ImageComponent(":/decorations/trees.png"));
    clouds = new Entity(nullptr, -200, -96, 600, 96);
    clouds->addComponent(new ImageComponent(":/decorations/clouds.png"));

    Entity* playerCredits = EntityFactory::playerCredits(QPointF(0,0), QSizeF(16, 32));
    Entity* cameraLock = new Entity(nullptr, 0, -38, 16, 16);

    Entity* fader = new Entity(nullptr, -1000, -1000, 2000, 2000);
    fader->addComponent(new TransitionComponent(
                [=]() {
                    delete fader;
                },
                [](QPainter* painter, const Entity* entity, int duration, int ticksPassed) {
                    if(ticksPassed < 60)
                    {
                            painter->fillRect(0, 0, entity->getSize().width(), entity->getSize().height(), Qt::black);
                    }
                    else
                    {
                            painter->fillRect(0, 0, entity->getSize().width(), entity->getSize().height(),
                                QColor(0, 0, 0, 255 - (255 * static_cast<float>(ticksPassed - 60) / (duration - 60))));
                    }
                }, 300
    ));

    this->addItem(sky);
    this->addItem(mountains);
    this->addItem(clouds);
    this->addItem(bushes);
    this->addItem(credits);
    this->addItem(thanks);
    this->addItem(bottom1);
    this->addItem(bottom2);
    this->addItem(playerCredits);
    this->addItem(cameraLock);
    this->addItem(fader);

    camera->attachTo(cameraLock);
}

CreditsScene::~CreditsScene()
{

}

void CreditsScene::update()
{
    bottom1->setPos(bottom1->pos() - QPointF(0.5, 0));
    bottom2->setPos(bottom2->pos() - QPointF(0.5, 0));
    mountains->setPos(mountains->pos() - QPointF(0.002, 0));
    clouds->setPos(clouds->pos() - QPointF(0.03, 0));
    bushes->setPos(bushes->pos() - QPointF(0.05, 0));

    if(credits->pos().y() > -1000)
    {
        credits->setPos(credits->pos() - QPointF(0, 0.6));
    }

    if(thanks->pos().y() > -50)
    {
        thanks->setPos(thanks->pos() - QPointF(0, 0.6));
    }
    else
    {
        Entity* fader = new Entity(nullptr, -1000, -1000, 2000, 2000);
        fader->addComponent(new TransitionComponent(
                    [=]() {
                        this->game->switchScene("menu");
                    },
                    [](QPainter* painter, const Entity* entity, int duration, int ticksPassed) {
                        if(ticksPassed < 60)
                        {
                                painter->fillRect(0, 0, entity->getSize().width(), entity->getSize().height(), Qt::transparent);
                        }
                        else
                        {
                                painter->fillRect(0, 0, entity->getSize().width(), entity->getSize().height(),
                                    QColor(0, 0, 0, (255 * static_cast<float>(ticksPassed - 60) / (duration - 60))));
                        }
                    }, 150
        ));
        this->addItem(fader);
    }

    if(bottom1->pos().x() <= -256 && bottom1First)
    {
        bottom2->setPos(QPointF(256, 32));
        bottom1First = false;
    }

    if(bottom2->pos().x() <= -256 && !bottom1First)
    {
        bottom1->setPos(QPointF(256, 32));
        bottom1First = true;
    }
}

void CreditsScene::onKeyChange(Input &input)
{

}
