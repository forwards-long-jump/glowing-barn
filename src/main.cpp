#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.processEvents();

    return a.exec();
}
