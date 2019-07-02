#ifndef TERRAINVIEW_H
#define TERRAINVIEW_H

#include <QWidget>
#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "algos/terrain_data.h"

namespace PTG {
namespace view {
class TerrainView : public QWidget
{
    Q_OBJECT

public:
    /*
     * Constructs a Terrain view based on a given terrain data.
     */
    TerrainView(QWidget *parent = nullptr);
    virtual ~TerrainView();

    /*
     * Exports terrain view as a .png image and saves it
     * on the harddrive.
     * @param path the path to save the .png at.
     * @param float the scale to save the .png as.
    */
    void exportPNG(const QString & path, float scale = 1.0);

    /*
     * Prints a given terrain data object onto the scene view.
     * Printing will then be managed internally by QGraphicsView.
     * @param obj the terrain data object to draw from.
     */
    void printScence(const data::TerrainData& obj);

    /*
     * Clears the QGraphis scene.
     */
    void clearScence();

    /*
     * Sets the zoom level for this view.
     */
    void setZoom(const int & zoom);

    /*
     * Gets the zoom level for this view.
     */
    int getZoom();

private:
    // From -2 to 2
    int zoomLevel = 0;

    QGraphicsScene * scene;
    QGraphicsView * view;
};
}
}


#endif // TERRAINVIEW_H
