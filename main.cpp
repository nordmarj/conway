#include "scene.h"
#include "game.h"
#include <vector>
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    int s = 50;
    Scene scene(s,s,5);
    QGraphicsView view(&scene);
    view.show();

    return a.exec();
}
