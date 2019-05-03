#include "terrainview.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TerrainView w;
    w.show();

    return a.exec();
}
