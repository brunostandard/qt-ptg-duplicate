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
    data::DiamondSquare ds(513);
    ds();
    std::vector<std::vector<int>> map = ds.getMap();

    for(size_t y = 0; y < 513; y++)
    {
        for(size_t x = 0; x < 513; x++)
        {
            size_t xSize = 4;
            size_t ySize = 4;

            QPixmap p = QPixmap(xSize,ySize);

            //Fill
            int value = map[x][y];

            if(value < 130)
                p.fill(Qt::darkBlue);
            else if(value < 150)
                p.fill(Qt::blue);
            else if(value < 200)
                p.fill(Qt::darkGreen);
            else if(value < 230)
                p.fill(Qt::darkYellow);
            else if(value < 250)
                p.fill(Qt::gray);
            else if(value < 260)
                p.fill(Qt::darkGray);
            else
                p.fill(Qt::white);

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
