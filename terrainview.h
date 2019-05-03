#ifndef TERRAIN_VIEW_H
#define TERRAIN_VIEW_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>

namespace PTG{
namespace view{
    class TerrainView : public QWidget
    {
        Q_OBJECT

    public:
        TerrainView(QWidget *parent = nullptr);
        ~TerrainView();
    private:
        QGraphicsScene * scene;
        QGraphicsView * view;
    };
    }
}

#endif // TERRAIN_VIEW_H
