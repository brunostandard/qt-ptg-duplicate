#ifndef SECONDPAGE_H
#define SECONDPAGE_H

#include "page.h"
#include <QHBoxLayout>
#include <QComboBox>
#include "algos/diamond_square.h"
namespace PTG {
    namespace view {
        class SecondPage : public Page
        {
            Q_OBJECT
        public:
            explicit SecondPage(QWidget *parent = nullptr);

        private:
            PTG::back::DiamondSquare obj;

            QPushButton * nextButton = nullptr;

            QPushButton * prevButton = nullptr;

            QComboBox * resolutionComboBox = nullptr;

            QLabel * resolutionLabel = nullptr;

            QComboBox * windowSizeComboBox = nullptr;

            QLabel * windowLabel = nullptr;

            QLabel * seaLevelLabel = nullptr;

            QSlider * seaLevelSlider = nullptr;

            QLabel * seaLevelSliderValue = nullptr;

            QHBoxLayout * seaLevelParamContainer = nullptr;

            void initializeWidgets();
            void setWidgetsToLayout();
        public slots:
            void nextButtonPushed();
            void prevButtonPushed();
            void setPageStyle() override;
        signals:
            void setMapParams(int,const std::vector<std::vector<int>>&);
        };
    }
}
#endif // SECONDPAGE_H
