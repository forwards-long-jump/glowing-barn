#include "menuscene.h"

MenuScene::MenuScene(QString name, Game* game)
    : Scene(name, game)
{
    //Decorations
    Entity* bottom1 = new Entity(nullptr, 0, 32, 512, 48);
    bottom1->addComponent(new ImageComponent(":/credits/background.png"));
    Entity* bottom2 = new Entity(nullptr, -512, 32, 512, 48);
    bottom2->addComponent(new ImageComponent(":/credits/background.png"));
    Entity* sky = new Entity(nullptr, -200, -200, 900, 300);
    sky->addComponent(new ImageComponent(":/decorations/sky.png"));
    sky->addComponent(new ParallaxComponent(1));
    Entity* mountains = new Entity(nullptr, -200, -64, 400, 96);
    mountains->addComponent(new ImageComponent(":/decorations/mountains.png"));
    Entity* bushes = new Entity(nullptr, -200, -46, 400, 96);
    bushes->addComponent(new ImageComponent(":/decorations/trees.png"));
    clouds1 = new Entity(nullptr, 0, -96, 600, 96);
    clouds1->addComponent(new ImageComponent(":/decorations/clouds.png"));
    clouds2 = new Entity(nullptr, -600, -96, 600, 96);
    clouds2->addComponent(new ImageComponent(":/decorations/clouds.png"));
    Entity* title = new Entity(nullptr, -76, -60, 152, 34);
    title->addComponent(new ImageComponent(":menu/title.png"));
    Entity* start = new Entity(nullptr, -45.25, -3.125 , 80.5, 6.25);
    start->addComponent(new ImageComponent(":menu/start.png"));
    start->addComponent(new GenericRenderComponent([](QPainter* painter, Entity*, int tick) {
        painter->setOpacity(qAbs(qSin(static_cast<double>(tick)/30)));
    }));

    Entity* cameraLock = new Entity(nullptr, -8, -38, 16, 16);

    leaveFader = new Entity(nullptr, -1000, -1000, 2000, 2000);
    leaveFader->setZValue(10000);
    leaveFader->addComponent(new TransitionComponent(
                [=]() {
                    game->switchScene("game");
                },
                [](QPainter* painter, const Entity* entity, int duration, int ticksPassed) {
                    painter->fillRect(0, 0, entity->getSize().width(), entity->getSize().height(),
                        QColor(0, 0, 0, (255 * static_cast<float>(ticksPassed) / duration)));
                }, 40, false
    ));
    enterFader = new Entity(nullptr, -1000, -1000, 2000, 2000);
    enterFader->setZValue(10000);
    enterFader->addComponent(new TransitionComponent(
                [=]() {},
                [](QPainter* painter, const Entity* entity, int duration, int ticksPassed) {
                    if(ticksPassed < 20)
                    {
                            painter->fillRect(0, 0, entity->getSize().width(), entity->getSize().height(), Qt::white);
                    }
                    else
                    {
                            painter->fillRect(0, 0, entity->getSize().width(), entity->getSize().height(),
                                QColor(255, 255, 255, 255 - (255 * static_cast<float>(ticksPassed - 20) / (duration - 20))));
                    }
                }, 100, false
    ));

    this->addItem(sky);
    this->addItem(mountains);
    this->addItem(clouds1);
    this->addItem(clouds2);
    this->addItem(bushes);
    this->addItem(bottom1);
    this->addItem(bottom2);
    this->addItem(cameraLock);
    this->addItem(title);
    this->addItem(start);
    this->addItem(enterFader);
    this->addItem(leaveFader);

    camera->attachTo(cameraLock);
}

MenuScene::~MenuScene()
{

}

void MenuScene::onEnter()
{
    Sounds::fadeOut(20, "/assets/sounds/menu.mp3");
    if(!game->isPaused())
        static_cast<TransitionComponent*>(enterFader->getComponent("TransitionComponent"))->restart();
    else
        game->togglePaused();
}

void MenuScene::update()
{
    clouds1->setPos(clouds1->pos() - QPointF(1, 0));
    clouds2->setPos(clouds2->pos() - QPointF(1, 0));

    if(clouds1->pos().x() <= -300 && clouds1First)
    {
        clouds2->setPos(QPointF(300, -96));
        clouds1First = false;
    }

    if(clouds2->pos().x() <= -300 && !clouds1First)
    {
        clouds1->setPos(QPointF(300, -96));
        clouds1First = true;
    }
}

void MenuScene::onKeyChange(Input&)
{
    // Handle start the game
    if(Game::input.isKeyDown(Input::Key::START_GAME) || Game::input.isKeyDown(Input::Key::START_GAME2))
    {
        static_cast<TransitionComponent*>(leaveFader->getComponent("TransitionComponent"))->restart();
    }
}
