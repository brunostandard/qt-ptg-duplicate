#include "generationpage.h"
#include <QDebug>
#include <QFontDatabase>
#include "view/ptgbutton.h"

namespace PTG {
    namespace view {
        GenerationPage::GenerationPage(QWidget *parent) : Page(parent),
          heightMap(static_cast<size_t>(pow(2,4)+1)),
          nextButton(new PTGButton),
          backButton(new PTGButton),
          resolutionComboBox(new QComboBox),
          resolutionLabel(new QLabel),
          seaLevelLabel(new QLabel),
          seaLevelSlider(new QSlider(Qt::Horizontal)),
          seaLevelSliderValue(new QLabel),
          hillLevelLabel(new QLabel),
          hillLevelSlider(new QSlider(Qt::Horizontal)),
          hillLevelSliderValue(new QLabel),
          mountLevelLabel(new QLabel),
          mountLevelSlider(new QSlider(Qt::Horizontal)),
          mountLevelSliderValue(new QLabel),
          seaLevelParamContainer(new QHBoxLayout),
          hillLevelParamContainer(new QHBoxLayout),
          mountLevelParamContainer(new QHBoxLayout),
          viewButton(new PTGButton),
          refreshButton(new PTGButton),
          terrainImage(new TerrainView(this))
        {
            heightMap(); // generate the height map with content

            qDebug() << "GenerationPage::GenerationPage()";

            initializeWidgets(); // initialize the widgets with texts and such

            setWidgetsToLayout(); // set widgets to a certain ordering

            setPageLayout(); // set the (page) layout of widget

            setConnections(); // set the button, sliders, and combo box connections

            setPageStyle();

        }

        GenerationPage::~GenerationPage()
        {

        }

        void GenerationPage::setConnections() {
            // connect page buttons
            QObject::connect(nextButton,SIGNAL(clicked()),this,SLOT(nextButtonPushed()));
            QObject::connect(backButton,SIGNAL(clicked()),this,SLOT(backButtonPushed()));
            QObject::connect(viewButton,SIGNAL(clicked()),this,SLOT(viewButtonPushed()));
            QObject::connect(refreshButton,SIGNAL(clicked()),this,SLOT(refreshButtonPushed()));

            // connection sliders
            QObject::connect(seaLevelSlider, SIGNAL(valueChanged(int)), seaLevelSliderValue,
            SLOT(setNum(int)));
            QObject::connect(hillLevelSlider, SIGNAL(valueChanged(int)), hillLevelSliderValue,
            SLOT(setNum(int)));
            QObject::connect(mountLevelSlider, SIGNAL(valueChanged(int)), mountLevelSliderValue,
            SLOT(setNum(int)));

            // sea level < hill level < mount level
            QObject::connect(seaLevelSlider, SIGNAL(valueChanged(int)),
                             this, SLOT(updateSliders(int)));
            QObject::connect(hillLevelSlider, SIGNAL(valueChanged(int)),
                             this, SLOT(updateSliders(int)));
            QObject::connect(mountLevelSlider, SIGNAL(valueChanged(int)),
                             this, SLOT(updateSliders(int)));

            // update the height-map when combo-box resolution changes
            QObject::connect(resolutionComboBox, SIGNAL(currentIndexChanged(int)),
                             this, SLOT(updateHeightMap(int)));
        }

        void GenerationPage::initializeWidgets(){
            // add text to buttons
            nextButton->setText("Generate");
            backButton->setText("Back");
            viewButton->setText("View");
            refreshButton->setText("Refresh");

            // resolution paramter
            resolutionLabel->setText("Select Map Size:");
            resolutionComboBox->addItem("Very Small (170x170 pixels)");
            resolutionComboBox->addItem("Small (330x330 pixels)");
            resolutionComboBox->addItem("Medium (650x650 pixels)");
            resolutionComboBox->addItem("Large (1290x1290 pixels)");
            resolutionComboBox->addItem("Very Large (2560x2560 pixels)");

            // sea level parameter
            seaLevelLabel->setText("Select average Sea Level: ");
            seaLevelSlider->setRange(10,280);
            seaLevelSlider->setValue(120);
            seaLevelSliderValue->setText("50");

            // hill level parameter
            hillLevelLabel->setText("Select average Hill Level: ");
            hillLevelSlider->setRange(20,290);
            hillLevelSlider->setValue(150);
            hillLevelSliderValue->setText("60");

            // mountain level paramter
            mountLevelLabel->setText("Select average Mount Level: ");
            mountLevelSlider->setRange(30,310);
            mountLevelSlider->setValue(200);
            mountLevelSliderValue->setText("70");
        }


        void GenerationPage::setWidgetsToLayout(){
            addPageWidget(resolutionLabel,0,0);
            addPageWidget(resolutionComboBox,0,1);

            seaLevelParamContainer->addWidget(seaLevelSlider);
            seaLevelParamContainer->addWidget(seaLevelSliderValue);

            hillLevelParamContainer->addWidget(hillLevelSlider);
            hillLevelParamContainer->addWidget(hillLevelSliderValue);

            mountLevelParamContainer->addWidget(mountLevelSlider);
            mountLevelParamContainer->addWidget(mountLevelSliderValue);

            QVBoxLayout * labelLayout = new QVBoxLayout();
            labelLayout->addWidget(seaLevelLabel);
            labelLayout->addWidget(hillLevelLabel);
            labelLayout->addWidget(mountLevelLabel);

            addLayout(labelLayout,2,0);

            QVBoxLayout * controlLayout = new QVBoxLayout();
            controlLayout->addLayout(seaLevelParamContainer);
            controlLayout->addLayout(hillLevelParamContainer);
            controlLayout->addLayout(mountLevelParamContainer);

            addLayout(controlLayout,2,1);

            // add buttons
            addPageWidget(nextButton,5,1);
            addPageWidget(backButton,5,0);
            addPageWidget(viewButton,0,3);
            addPageWidget(refreshButton,1,3);

            // add terrainImage
            addPageWidget(terrainImage,2,3);
        }


        void GenerationPage::nextButtonPushed(){
            qDebug() << "GenerationPage::nextButtonPushed()";
            // get the parameter values
            int k = seaLevelSlider->value();
            int j = hillLevelSlider->value();
            int i = mountLevelSlider->value();
            // send a signal with these values
            emit setMapParams(heightMap,k,j,i);
            qDebug() << k << " " << j << " " << i;
            emit Page::setPage(2); // emit signal corresonding to the terrain page
        }


        void GenerationPage::backButtonPushed(){
            qDebug() << "GenerationPage::backButtonPushed";
            emit Page::setPage(0); // emit signal corresponding to the welcome page
        }

        void GenerationPage::viewButtonPushed() {
            qDebug() << "GeneratePage::viewButtonPushed()";
            // get the parameter values
            int k = seaLevelSlider->value();
            int j = hillLevelSlider->value();
            int i = mountLevelSlider->value();
            // create a terrain data object
            data::TerrainData obj2(heightMap,k,j,i);
            // clear whatever was currently printed
            terrainImage->clearScence();
            // reprint the scence with the current Terrain Data obj2
            terrainImage->printScence(obj2);

        }

        void GenerationPage::refreshButtonPushed() {
            qDebug() << "GeneratePage::refreshButtonPushed()";
            // get the parameter values (if they have changed at all)
            int k = seaLevelSlider->value();
            int j = hillLevelSlider->value();
            int i = mountLevelSlider->value();

            heightMap(); // regenerate the height map
            // create a terrain data object
            data::TerrainData obj2(heightMap,k,j,i);
            // clear whatever was currently printed
            terrainImage->clearScence();
            // reprint the scence with the current Terrain Data obj2
            terrainImage->printScence(obj2);
        }
        void GenerationPage::updateSliders(int) {
            // get the most updated slider values
            int s = seaLevelSlider->value();
            int h = hillLevelSlider->value();
            int m = mountLevelSlider->value();
            // if h is too close to s
            if (h-10 < s) {
                hillLevelSlider->setValue(s+10); // re-adjust value
            }
            // if m is too close to h
            if (m-10 < h) {
                mountLevelSlider->setValue(h+10); // re-adjust value
            }

        }

        void GenerationPage::updateHeightMap(int k) {
            size_t n = static_cast<size_t>(k+4); // get the combo box value
            size_t sz = static_cast<size_t>(pow(2,n)+1); // formula..
            heightMap.setMap(sz); // prepare the height map with this new size
            heightMap(); // generate the height map
        }

        void GenerationPage::setPageStyle(){
            Page::setPageStyle(); // add page styling, but we are going to add more though..
            QString copy = "font-size: 50px;"
                           "font-variant: small-caps;"
                           "font-weight: bold;"
                           "background-color: rgba(40,25,20, .6);"
                           "text-align: center;";
            nextButton->setStyleSheet(copy);
            backButton->setStyleSheet(copy);

            if(QFontDatabase::addApplicationFont(":/font/monogram.ttf"))
                qDebug("font loaded");
            QFont monogram("monogram");
            // give everything the monogram text
            setFont(monogram);
            resolutionLabel->setFont(monogram);
            seaLevelLabel->setFont(monogram);
            seaLevelSliderValue->setFont(monogram);
            hillLevelLabel->setFont(monogram);
            hillLevelSliderValue->setFont(monogram);
            mountLevelLabel->setFont(monogram);
            mountLevelSliderValue->setFont(monogram);
            nextButton->setFont(monogram);
            backButton->setFont(monogram);
            viewButton->setFont(monogram);
            refreshButton->setFont(monogram);
            resolutionComboBox->setFont(monogram);
        }
    }
}
