#include "secondpage.h"
#include <QDebug>
namespace PTG {
    namespace view {
        SecondPage::SecondPage(QWidget *parent) : Page(parent),
          nextButton(new QPushButton),
          prevButton(new QPushButton),
          resolutionComboBox(new QComboBox),
          resolutionLabel(new QLabel),
          windowSizeComboBox(new QComboBox),
          windowLabel(new QLabel),
          seaLevelLabel(new QLabel),
          seaLevelSlider(new QSlider(Qt::Horizontal)),
          seaLevelSliderValue(new QLabel),
          seaLevelParamContainer(new QHBoxLayout)
        {

            qDebug() << "SecondPage()\n";

            initializeWidgets();

            setWidgetsToLayout();

            setPageLayout();

            QObject::connect(nextButton,SIGNAL(clicked()),this,SLOT(nextButtonPushed()));

            QObject::connect(prevButton,SIGNAL(clicked()),this,SLOT(prevButtonPushed()));

            QObject::connect(seaLevelSlider, SIGNAL(valueChanged(int)), seaLevelSliderValue,
            SLOT(setNum(int)));

            setPageStyle();

        }


        void SecondPage::initializeWidgets(){

            nextButton->setText("Generate");
            prevButton->setText("Back");

            resolutionLabel->setText("Select Resoultion: ");
            resolutionComboBox->addItem("Medium (20x20 pixels)");
            resolutionComboBox->addItem("High (10x10 pixels)");
            resolutionComboBox->addItem("Ultra (5x5 pixels)");


            windowLabel->setText("Select Window Size: ");
            windowSizeComboBox->addItem("Small (452x452)");
            windowSizeComboBox->addItem("Medium (640x640)");
            windowSizeComboBox->addItem("Large (905x905)");
            windowSizeComboBox->addItem("Extra-Large (1280x1280)");

            seaLevelLabel->setText("Select average Sea Level: ");
            seaLevelSlider->setRange(-100,100);
            seaLevelSliderValue->setText("0");


        }


        void SecondPage::setWidgetsToLayout(){
            addPageWidget(resolutionLabel,0,0);
            addPageWidget(resolutionComboBox,0,1);

            addPageWidget(windowLabel,1,0);
            addPageWidget(windowSizeComboBox,1,1);

            addPageWidget(seaLevelLabel,3,0);
            seaLevelParamContainer->addWidget(seaLevelSlider);
            seaLevelParamContainer->addWidget(seaLevelSliderValue);
            addLayout(seaLevelParamContainer,3,1);

            addPageWidget(nextButton,5,1);
            addPageWidget(prevButton,5,0);
        }


        void SecondPage::nextButtonPushed(){
            qDebug() << "Second page nextButton pushed\n";
            //int i = resolutionComboBox->currentIndex();
            //int j = windowSizeComboBox->currentIndex();
            int k = seaLevelSlider->value();
            obj.setMap(10);
            obj();
            emit setMapParams(k,obj.getMap());
            emit Page::setPage(2);
        }


        void SecondPage::prevButtonPushed(){
            qDebug() << "Second page prevButton pushed\n";
            emit Page::setPage(0);
        }


        void SecondPage::setPageStyle(){
            QString copy = "border: 2px solid white;"
                           "color: white;"
                           "font-size: 22px;"
                           "border-radius: 4px;"
                           "padding: 2px;"
                           "text-align: center;";

            resolutionLabel->setStyleSheet(copy);
            windowLabel->setStyleSheet(copy);
            seaLevelLabel->setStyleSheet(copy);
            seaLevelSliderValue->setStyleSheet(copy);
        }
    }
}
