#include "terrainview.h"
#include <QDebug>
#include <QFontDatabase>
#include "view/ptgbutton.h"
#include <QVBoxLayout>
#include <QGraphicsPixmapItem>
#include <QRandomGenerator>
#include <QFileDialog>

namespace PTG {
namespace view {
TerrainView::TerrainView(QWidget *parent)
    : QWidget(parent)
{
    qDebug() << "TerrainView::TerrainView()";
    // Create the graphics scene and view for this terrain view
    scene = new QGraphicsScene();
    view = new QGraphicsView(scene);
    QLayout * layout = new QVBoxLayout();
    layout->addWidget(view);
    this->setLayout(layout);

}

void TerrainView::printScence(const data::TerrainData& obj) {
    auto & map = obj.height;
    for(size_t y = 0; y < map.size(); y++)
    {
        for(size_t x = 0; x < map[0].size(); x++)
        {
            size_t xSize = 10;
            size_t ySize = 10;

            QPixmap p = QPixmap(xSize, ySize);
            double value = map[y][x];

            if (value < obj.sea_level-50) {
                p = QPixmap(":/textures/ocean.png");

            }
            else if ((obj.sea_level-50 <= value)&&(value < obj.sea_level)){
                p = QPixmap(":/textures/coast.png");

            }
            //else if ((obj.sea_level-10 <= value)&&(value < obj.sea_level)){
            //    p = QPixmap(":/textures/coast.png");
            //
            //}
            else{
                QString str = obj.get_land_art(y,x);
                p = QPixmap(str);
            }
            QGraphicsPixmapItem * pi = new QGraphicsPixmapItem(p);
            scene->addItem(pi);
            pi->setOffset(x*xSize,y*ySize);
        }
    }
    // Might have to resize scene based on map size.
    scene->setSceneRect(scene->itemsBoundingRect());
    qDebug() << "End.";

}

void TerrainView::clearScence() {
    if (scene) {
        scene->clear();
        scene->update();
    }
    // else, do nothing
    return;
}
TerrainView::~TerrainView()
{
    if (scene){
        delete scene;
    }
}

void TerrainView::exportPNG(const QString &path, float scale)
{
    int width = (scale * scene->width());
    int height = (scale * scene->height());

    // Create an image with the desired width and height.
    QImage image(width,height,QImage::Format_RGB16);
    // Create a painter context on top of this image.
    QPainter painter(&image);
    // Render the scene with painter.
    scene->render(&painter);
    // Save the created image at the given path.
    image.save(path);
}

void TerrainView::setZoom(const int & zoom)
{
    // No zoom, so return.
    if(zoom == zoomLevel){
        return;
    }
    // If zooming in
    else if(zoom > this->zoomLevel){
        view->scale(2,2);
    }
    // If zooming out
    else{

        view->scale(.5,.5);
    }
    zoomLevel = zoom;
}

int TerrainView::getZoom()
{
    return zoomLevel;
}

}
}
