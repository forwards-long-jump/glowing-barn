#ifndef MENUSCENE_H
#define MENUSCENE_H

#include <QPushButton>

#include "scene.h"

class MenuScene : public Scene
{
    Q_OBJECT

public:
    MenuScene(QString name = "default", Game *game = 0);
    ~MenuScene();

private:
    QPushButton *btnLaunch;
};

#endif // MENUSCENE_H
