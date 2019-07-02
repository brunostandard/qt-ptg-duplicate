#include "mainwindow.h"
#include <QDesktopWidget>
#include <QDebug>
#include <QMediaPlaylist>
#include "algos/diamond_square.h"
namespace PTG {
    namespace view {
        MainWindow::MainWindow(QWidget *parent)
            : QWidget(parent),
              player(new QMediaPlayer),
              pages(nullptr),
              main_layout(new QVBoxLayout),
              welcomePageWidget(nullptr),
              generationPageWidget(nullptr),
              lastPageWidget(nullptr),
              aboutPageWidget(nullptr),
              instructPageWidget(nullptr),
              pageComboBox(nullptr)
        {
            qDebug() << "MainWindow()\n";

            initMedia();

            setStackedPages(); // (void) the pages onto the StackedWidget called pages.

            //markPages(); // (void) mark pages with a QCombobBox object called pageComboBox.

            setConnections(); // (void) set the connections

            resize(QDesktopWidget().availableGeometry(this).size() * 0.4); // adjust window size

            // setting background, 1st page == 0, 2nd page == 1, ....
            // the slot function needs to be called manually each time the program starts.
            updateBackground(0);
            qDebug() << "MainWindow()\n";
         }

        MainWindow::~MainWindow()
        {
            if(player){
                   delete player;
            }
        }

        void MainWindow::setStackedPages(){
            // create pages.
            welcomePageWidget = new WelcomePage(this);
            generationPageWidget = new GenerationPage(this);
            lastPageWidget = new TerrainPage(this);
            aboutPageWidget = new AboutPage(this);
            instructPageWidget = new InstructionPage(this);
            // add pages to object pages.
            pages = new QStackedWidget(this);
            pages->addWidget(welcomePageWidget);
            pages->addWidget(generationPageWidget);
            pages->addWidget(lastPageWidget);
            pages->addWidget(aboutPageWidget);
            pages->addWidget(instructPageWidget);
            // create layout and add pages to layout
            main_layout = new QVBoxLayout;
            main_layout->addWidget(pages);
           //  set layout
            setLayout(main_layout);
        }

        void MainWindow::markPages(){
            // make combobox
            pageComboBox = new QComboBox(this);
            // hide it
            pageComboBox->hide();
            // mark pages
            pageComboBox->addItem(tr("Page 1"));
            pageComboBox->addItem(tr("Page 2"));
            pageComboBox->addItem(tr("Page 3"));
        }
        void MainWindow::setConnections(){
            // page changing part
            QObject::connect(welcomePageWidget, SIGNAL(setPage(int)),
                    pages, SLOT(setCurrentIndex(int)));
            QObject::connect(aboutPageWidget, SIGNAL(setPage(int)),
                    pages, SLOT(setCurrentIndex(int)));
            QObject::connect(instructPageWidget, SIGNAL(setPage(int)),
                    pages, SLOT(setCurrentIndex(int)));
            QObject::connect(generationPageWidget, SIGNAL(setPage(int)),
                    pages, SLOT(setCurrentIndex(int)));
            QObject::connect(lastPageWidget, SIGNAL(setPage(int)),
                    pages, SLOT(setCurrentIndex(int)));

            // background changing part
            QObject::connect(welcomePageWidget, SIGNAL(setPage(int)),
                    this, SLOT(updateBackground(int)));
            QObject::connect(aboutPageWidget, SIGNAL(setPage(int)),
                    this, SLOT(updateBackground(int)));
            QObject::connect(instructPageWidget, SIGNAL(setPage(int)),
                    this, SLOT(updateBackground(int)));
            QObject::connect(generationPageWidget, SIGNAL(setPage(int)),
                    this, SLOT(updateBackground(int)));
            QObject::connect(lastPageWidget, SIGNAL(setPage(int)),
                    this, SLOT(updateBackground(int)));

            // map part
            QObject::connect(generationPageWidget, SIGNAL(setMapParams(data::DiamondSquare,int,int,int)),
                    lastPageWidget, SLOT(getMapParams(data::DiamondSquare,int,int,int)));

            // Media part
            QObject::connect(welcomePageWidget, SIGNAL(muteButtonClicked()),
                    this, SLOT(stopMediaSounds()));

            // Instruction Page
            QObject::connect(welcomePageWidget, SIGNAL(instructButtonClicked()),
                             instructPageWidget, SLOT(instructionPageInView()));
        }

        void MainWindow::updateBackground(int page_number){
            QString qstr = ":/fig/terrain.png";
            // change the file directory depending on page number.
            switch (page_number){
            case 0:
                qstr = ":/fig/terrain.png";
                break;
            case 1:
                qstr = ":/fig/background.png";
                break;
            case 2:
                qstr = ":/fig/background.png";
                break;
            default:
                return;
            }
            // set background.
            QPixmap bkgnd(qstr);
            bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
            QPalette palette;
            palette.setBrush(QPalette::Background, bkgnd);
            setPalette(palette);
            return;
        }

        void MainWindow::initMedia()
        {
            // Create playlist for media player.
            auto playlist = new QMediaPlaylist;
            playlist->addMedia(QUrl("qrc:/sounds/ambient_1.mp3"));
            playlist->setPlaybackMode(QMediaPlaylist::Loop);
            player->setPlaylist(playlist);
            player->setVolume(60);
            player->play();
        }
        void MainWindow::stopMediaSounds() {
            player->stop();
        }
    }

}
