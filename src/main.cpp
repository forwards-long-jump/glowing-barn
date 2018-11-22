#include <QApplication>

#include "include/game.h"
#include "include/rectanglecomponent.h"
#include "include/entity.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Game game;

    game.setScene(scene);
    game.resize(1280, 720);

    game.show();

    return a.exec();
}
