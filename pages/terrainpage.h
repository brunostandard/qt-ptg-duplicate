#ifndef TERRAINPAGE_H
#define TERRAINPAGE_H

#include "page.h"
#include "algos/terrain_data.h"
#include "view/terrainview.h"
#include "view/terraintools.h"
#include <QPixmap>
namespace PTG {
    namespace view {
    /**
     * @brief The TerrainView class displays an instructions for using the project.
     */
        class TerrainView;

        /**
         * @brief The TerrainPage class contains a visualization of the terrain
         * and tools to interract with the terrain..
         */
        class TerrainPage : public Page
        {
            Q_OBJECT
        public:

            explicit TerrainPage(QWidget *parent = nullptr);

            virtual ~TerrainPage() override;

        private:

            QPushButton * backButton = nullptr;
            QPushButton * legendButton = nullptr;
            QLabel * legendTable = nullptr;
            QPixmap legendPixmapTable;
            TerrainTools * tools = nullptr;
            TerrainView * image = nullptr;

        public slots:

            /**
             * @brief backButtonPushed sets the current page to the Generation page.
             */
            void backButtonPushed();

            /**
             * @brief legendButtonPushed toggles the visibility of the biome legend.
             */
            void legendButtonPushed();

            /**
             * @brief setPageStyle initializes the stylesheet and fonts for this page.
             */
            void setPageStyle() override;

            /**
             * @brief getMapParams
             */
            void getMapParams(data::DiamondSquare,int,int,int);

            /**
             * @brief Zooms this page's image in, up to 4x.
             */
            void zoomIn();

            /**
             * @brief Zooms this page's image out, down to .25x.
             */
            void zoomOut();

            /**
             * @brief Creates an file dialogue,
             * which will call exportPNG() on the view.
             */
            void exportPNG();

        };

    }
}
#endif // TERRAINPAGE_H
