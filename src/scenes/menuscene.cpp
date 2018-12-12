#include "menuscene.h"

MenuScene::MenuScene(QString name, Game *game)
    : Scene(name, game)
{
    this->btnLaunch = new QPushButton(tr("Launch Game"));

    camera->setScaling(1);

    connect(btnLaunch, &QPushButton::clicked, [game](bool checked){
        game->switchScene("game");
    });

    this->addWidget(btnLaunch);
}

MenuScene::~MenuScene()
{

}
