#ifndef CREDITSSCENE_H
#define CREDITSSCENE_H

#include "scene.h"
#include "transitioncomponent.h"

/**
 * Scene for the staff roll and credits
 *
 * @authors Alexandre Bianchi, Pierre Bürki, Loïck Jeanneret
 */

class CreditsScene : public Scene
{
public:
    CreditsScene(QString name = "default", Game* game = 0);
    ~CreditsScene();

    void onEnter() override;
    void onLeave() override;

private:
    void onKeyChange(Input &input) override;
    void update() override;

    bool changeMapScheduled = false;
    QString newMapPath = "";
    QString newMapSpawn = "";

    Entity* bottom1;
    Entity* bottom2;
    Entity* credits;
    Entity* thanks;
    Entity* mountains;
    Entity* clouds;
    Entity* bushes;
    bool bottom1First = true;
};

#endif // CREDITSSCENE_H
