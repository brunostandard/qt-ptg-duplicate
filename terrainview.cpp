#include "terrainview.h"
#include <QVBoxLayout>
#include <QGraphicsPixmapItem>
#include <QRandomGenerator>

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
    QRandomGenerator random;
    random.seed(100);
    for(size_t y = 0; y < 250; y++)
    {
        for(size_t x = 0; x < 250; x++)
        {
            size_t xSize = 8;
            size_t ySize = 8;

            QPixmap p = QPixmap(xSize,ySize);

            // Randomize
            int r = random.bounded(10);

            if(r < 1)
                p.fill(Qt::darkBlue);
            else if(r < 6)
                p.fill(Qt::blue);
            else if(r < 9)
                p.fill(Qt::darkGreen);
            else if(r < 10)
                p.fill(Qt::gray);

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
