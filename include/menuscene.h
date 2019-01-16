#ifndef MENUSCENE_H
#define MENUSCENE_H

#include "scene.h"
#include "entity.h"

class MenuScene : public Scene
{
    Q_OBJECT

public:
    MenuScene(QString name = "default", Game* game = 0);
    ~MenuScene();

    void onEnter() override;
    void onKeyChange(Input&) override;
    void update() override;

private:
    Entity* enterFader;
    Entity* leaveFader;
    Entity* clouds1;
    Entity* clouds2;
    bool clouds1First = true;
};

#endif // MENUSCENE_H
