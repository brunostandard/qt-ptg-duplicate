#ifndef TERRAINTOOLS_H
#define TERRAINTOOLS_H

#include <QWidget>
#include "view/ptgbutton.h"

namespace PTG{
namespace view{
/*
 * TerrainTools contains buttons for tools to interract with the terrain,
 * such as exporting, zooming in, and zooming out.
 */
class TerrainTools: public QWidget
{
public:
    /*
     * Constructs a default TerrainTools instance.
     */
    TerrainTools();
    virtual ~TerrainTools();

    /*
     * Gets exportButton
     */
    PTGButton * getExportButton();
    /*
     * Gets zoomInButton
     */
    PTGButton * getZoomInButton();
    /*
     * Gets zoomOutButton
     */
    PTGButton * getZoomOutButton();

private:
    // Tool buttons
    PTGButton * exportButton = nullptr;
    PTGButton * zoomInButton = nullptr;
    PTGButton * zoomOutButton = nullptr;

    /*
     * Initializes the styles for this TerrainTools widget.
     * This is called in the constructor.
     */
    void _initStyles();

    /*
     * Initializes the layout for this TerrainTools widget.
     * This is called in the constructor.
     */
    void _initLayout();
};

}
}
#endif // TERRAINTOOLS_H
