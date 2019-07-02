#include "terraintools.h"
#include <QFontDatabase>

#include <QLayout>

namespace PTG{
namespace view{
TerrainTools::TerrainTools()
{
    _initLayout();
    _initStyles();
}

TerrainTools::~TerrainTools()
{

}

PTGButton * TerrainTools::getExportButton()
{
    return exportButton;
}

PTGButton * TerrainTools::getZoomInButton()
{
    return zoomInButton;
}

PTGButton * TerrainTools::getZoomOutButton()
{
    return zoomOutButton;
}

void TerrainTools::_initStyles()
{
    QString ssheet("border: 2px solid white;"
                   "color: white;"
                   "font-size: 50px;"
                   "font-variant: small-caps;"
                   "border-radius: 2px;"
                   "border-color: white;"
                   "padding: 2px;"
                   "text-align: center;"
                   "background-color: rgb(0,0,0,120)");
    this->setStyleSheet(ssheet);
    this->exportButton->setStyleSheet(ssheet);
    this->setStyleSheet(ssheet);
    this->zoomInButton->setStyleSheet(ssheet);
    this->setStyleSheet(ssheet);
    this->zoomOutButton->setStyleSheet(ssheet);

    if(QFontDatabase::addApplicationFont(":/font/monogram.ttf"))
        qDebug("font loaded");
    QFont monogram("monogram");
    this->setFont(monogram);
    this->exportButton->setFont(monogram);
    this->zoomInButton->setFont(monogram);
    this->zoomOutButton->setFont(monogram);

}

void TerrainTools::_initLayout()
{
    auto layout = new QVBoxLayout();
    exportButton = new PTGButton();
    exportButton->setText("Export .png");
    zoomInButton = new PTGButton();
    zoomInButton->setText("Zoom in");
    zoomOutButton = new PTGButton();
    zoomOutButton->setText("Zoom out");
    layout->addWidget(exportButton);
    layout->addWidget(zoomInButton);
    layout->addWidget(zoomOutButton);
    this->setLayout(layout);
}

}
}

