#include "mainwindow.h"
#include <QApplication>
#include <QFontDatabase>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    PTG::view::MainWindow w;
    w.show();

    return a.exec();
}
