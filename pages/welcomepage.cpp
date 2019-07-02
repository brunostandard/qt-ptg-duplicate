#include "welcomepage.h"
#include <QDebug>
#include <QFontDatabase>
#include "view/ptgbutton.h"

namespace PTG {
    namespace view {
        WelcomePage::WelcomePage(QWidget *parent) : Page(parent),
            title(new QLabel),
            newTerrainButton(new PTGButton),
            aboutButton(new PTGButton),
            instructButton(new PTGButton),
            quitButton(new PTGButton),
            muteButton(new PTGButton),
            temp_button_row_layout(new QHBoxLayout)
          {
            qDebug() << "WelcomePage()";

            title->setText("Procedural Terrain Generator");
            title->setAlignment(Qt::AlignCenter);
            newTerrainButton->setText("New Terrain");
            aboutButton->setText("About");
            instructButton->setText("Instructions");
            quitButton->setText("Quit");
            muteButton->setText("Mute");

            qDebug() << "widgets set";
            addPageWidget(title);

            addPageWidget(newTerrainButton);
            addPageWidget(aboutButton);
            addPageWidget(instructButton);
            temp_button_row_layout->addWidget(quitButton);
            temp_button_row_layout->addWidget(muteButton);
            addLayout(temp_button_row_layout,5,0);
            setPageLayout();

            QObject::connect(newTerrainButton,SIGNAL(clicked()),this,SLOT(nextButtonPushed()));
            QObject::connect(aboutButton,SIGNAL(clicked()),this,SLOT(aboutButtonPushed()));
            QObject::connect(instructButton,SIGNAL(clicked()),this,SLOT(instructButtonPushed()));
            QObject::connect(quitButton,SIGNAL(clicked()),
                             this->parentWidget(),SLOT(close()));
            QObject::connect(muteButton,SIGNAL(clicked()),
                             this,SLOT(muteButtonPushed()));
            setPageStyle();
            qDebug() << "end of WelcomePage()";
        }

        WelcomePage::~WelcomePage()
        {

        }

        void WelcomePage::nextButtonPushed() {
            qDebug() << "WelcomePage::nextButtonPushed()";
            emit Page::setPage(1);
        }

        void WelcomePage::aboutButtonPushed() {
            qDebug() << "WelcomePage::aboutButtonPushed()";
            emit Page::setPage(3);
        }

        void WelcomePage::instructButtonPushed() {
            qDebug() << "WelcomePage::instructButtonPushed()";
            emit Page::setPage(4);
            emit instructButtonClicked();
        }
        void WelcomePage::muteButtonPushed() {
            qDebug() << "WelcomePage::muteButtonPushed()";
            emit muteButtonClicked();
        }
        void WelcomePage::setPageStyle() {
            Page::setPageStyle();
            title->setStyleSheet("color: white;"
                              "font-size: 111px;"
                              "font-variant: small-caps;"
                              "font-weight: bold;"
                              "border-radius: 5px;"
                              "padding: 2px;"
                              "text-align: center;");

            if(QFontDatabase::addApplicationFont(":/font/monogram.ttf"))
                qDebug("font loaded");
            QFont monogram("monogram");
            title->setFont(monogram);
            newTerrainButton->setFont(monogram);
            aboutButton->setFont(monogram);
            instructButton->setFont(monogram);
            quitButton->setFont(monogram);
            muteButton->setFont(monogram);
        }
    }
}
