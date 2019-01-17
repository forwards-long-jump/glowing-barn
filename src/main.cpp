#include <QApplication>

#include "include/game.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    Game game;

    game.resize(1280, 720);
    game.showFullScreen();
    return a.exec();
}
