#ifndef GENERATIONPAGE_H
#define GENERATIONPAGE_H

#include "page.h"
#include <QHBoxLayout>
#include <QComboBox>
#include "algos/diamond_square.h"
#include "view/terrainview.h"
#include "algos/terrain_data.h"
namespace PTG {
    namespace view {
        /**
         * @brief The GenerationPage class contains all the user controls for terrain generation.
         */
        class GenerationPage : public Page
        {
            Q_OBJECT
        public:
            /**
             * @brief AboutPage initializes the content, styles, and connections of an about page.
             * @param parent the parent QWidget to use.
             */
            explicit GenerationPage(QWidget *parent = nullptr);

            virtual ~GenerationPage() override;

        private:
            PTG::data::DiamondSquare heightMap;

            QPushButton * nextButton = nullptr;
            QPushButton * backButton = nullptr;
            QComboBox * resolutionComboBox = nullptr;
            QLabel * resolutionLabel = nullptr;
            QLabel * seaLevelLabel = nullptr;
            QSlider * seaLevelSlider = nullptr;
            QLabel * seaLevelSliderValue = nullptr;
            QLabel * hillLevelLabel = nullptr;
            QSlider * hillLevelSlider = nullptr;
            QLabel * hillLevelSliderValue = nullptr;
            QLabel * mountLevelLabel = nullptr;
            QSlider * mountLevelSlider = nullptr;
            QLabel * mountLevelSliderValue = nullptr;
            QHBoxLayout * seaLevelParamContainer = nullptr; // containing slider and label
            QHBoxLayout * hillLevelParamContainer = nullptr; // containing slider and label
            QHBoxLayout * mountLevelParamContainer = nullptr; // containing slider and label

            QPushButton * viewButton = nullptr;
            QPushButton * refreshButton = nullptr;
            TerrainView * terrainImage = nullptr;

            /**
             * @brief initializeWidgets initializes the controls and other content of this page.
             */
            void initializeWidgets();

            /**
             * @brief setConnections initializes the connections fo this page.
             */
            void setConnections();

            /**
             * @brief setWidgetsToLayout initializes the layout of controls and other content on this page.
             */
            void setWidgetsToLayout();

        public slots:
            /**
             * @brief updateSliders updates the values of the sliders.
             */
            void updateSliders(int);

            /**
             * @brief nextButtonPushed changes the current page to the terrain page.
             */
            void nextButtonPushed();

            /**
             * @brief backButtonPushed changes the current page to the welcome page.
             */
            void backButtonPushed();

            /**
             * @brief viewButtonPushed views the terrain in a preview scene.
             */
            void viewButtonPushed();

            /**
             * @brief refreshButtonPushed  refreshes the height map being previewed.
             */
            void refreshButtonPushed();

            /**
             * @brief updateHeightMap updates the height map being previewed.
             */
            void updateHeightMap(int);

            /**
             * @brief setPageStyle initializes the styles on this page.
             */
            void setPageStyle() override;

        signals:
            /**
             * @brief setMapParams
             * @param DiamondSquare the heightmap to use
             * @param int sea level cutoff
             * @param int hill level cutoff
             * @param int mountain level cutoff
             */
            void setMapParams(data::DiamondSquare,int,int,int);
        };
    }
}
#endif // GENERATIONPAGE_H
