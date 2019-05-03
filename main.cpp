#include "terrainview.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PTG::view::TerrainView w;
    w.show();

    return a.exec();
}
