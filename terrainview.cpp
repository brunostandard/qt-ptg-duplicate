#include "terrainview.h"
#include <QVBoxLayout>
#include <QGraphicsPixmapItem>
#include <QRandomGenerator>
#include <vector>
#include "algos/diamond_square.h"

namespace PTG{
namespace view{
TerrainView::TerrainView(QWidget *parent)
    : QWidget(parent)
{
    // Create the graphics scene and view for this terrain view
    scene = new QGraphicsScene();
    view = new QGraphicsView(scene);
    QLayout * layout = new QVBoxLayout();
    layout->addWidget(view);
    this->setLayout(layout);
    // TEST ITEMS
    data::DiamondSquare ds(257);
    ds();
    std::vector<std::vector<int>> map = ds.getMap();

    for(size_t y = 0; y < 257; y++)
    {
        for(size_t x = 0; x < 257; x++)
        {
            size_t xSize = 4;
            size_t ySize = 4;

            QPixmap p = QPixmap(xSize, ySize);

            //Fill
            int value = map[x][y];

            if(value < 100)
                p = QPixmap("C:\\Users\\Timnus32\\Documents\\pic10c-ptg\\textures\\deepOcean.png");
            else if(value < 150)
                p = QPixmap("C:\\Users\\Timnus32\\Documents\\pic10c-ptg\\textures\\ocean.png");
            else if(value < 180)
                p = QPixmap("C:\\Users\\Timnus32\\Documents\\pic10c-ptg\\textures\\coast.png");
            else if(value < 225)
                p = QPixmap("C:\\Users\\Timnus32\\Documents\\pic10c-ptg\\textures\\land.png");
            else if(value < 250)
                p = QPixmap("C:\\Users\\Timnus32\\Documents\\pic10c-ptg\\textures\\hill.png");
            else if(value < 280)
                p = QPixmap("C:\\Users\\Timnus32\\Documents\\pic10c-ptg\\textures\\mountain.png");
            else
                p = QPixmap("C:\\Users\\Timnus32\\Documents\\pic10c-ptg\\textures\\peak.png");

            QGraphicsPixmapItem * pi = new QGraphicsPixmapItem(p);
            scene->addItem(pi);
            pi->setOffset(x*xSize,y*ySize);
        }
    }

}

TerrainView::~TerrainView()
{
    delete view;
}

}
}
