#include "mainwindow.h"
#include <QDesktopWidget>
#include <QDebug>
namespace PTG {
    namespace view {
        MainWindow::MainWindow(QWidget *parent)
            : QWidget(parent),
//              pages(nullptr),
              main_layout(new QVBoxLayout),
              firstPageWidget(nullptr)//,
//              secondPageWidget(nullptr),
//              lastPageWidget(nullptr),
//              pageComboBox(nullptr)
        {
            qDebug() << "MainWindow()\n";
            setStackedPages(); // (void) the pages onto the StackedWidget called pages.
            firstPageWidget = new FirstPage(this); // create first page

            main_layout->addWidget(firstPageWidget); // add page to layout
            setLayout(main_layout); // set layout

            //markPages(); // (void) mark pages with a QCombobBox object called pageComboBox.

            //setConnections(); // (void) set the connections

            resize(QDesktopWidget().availableGeometry(this).size() * 0.4); // adjust window size

            // setting background, 1st page == 0, 2nd page == 1, ....
            // the slot function needs to be called manually each time the program starts.
            //updateBackground(0);
            qDebug() << "MainWindow()\n";
         }

        MainWindow::~MainWindow()
        {

        }

        void MainWindow::setStackedPages(){
            // create pages.
//            firstPageWidget = new FirstPage(this);
//            secondPageWidget = new SecondPage(this);
//            lastPageWidget = new LastPage(this);
//            aboutPageWidget = new AboutPage(this);
            // add pages to object pages.
//            pages = new QStackedWidget(this);
//            pages->addWidget(firstPageWidget);
//            pages->addWidget(secondPageWidget);
//            pages->addWidget(lastPageWidget);
//            pages->addWidget(aboutPageWidget);
            // create layout and add pages to layout
//            main_layout = new QVBoxLayout;
//            main_layout->addWidget(pages);
            // set layout
//            setLayout(main_layout);
        }

        void MainWindow::markPages(){
            // make combobox
//            pageComboBox = new QComboBox(this);
            // hide it
//            pageComboBox->hide();
            // mark pages
//            pageComboBox->addItem(tr("Page 1"));
//            pageComboBox->addItem(tr("Page 2"));
//            pageComboBox->addItem(tr("Page 3"));
        }
        void MainWindow::setConnections(){
            // page changing part
//            QObject::connect(firstPageWidget, SIGNAL(setPage(int)),
//                    pages, SLOT(setCurrentIndex(int)));
//            QObject::connect(secondPageWidget, SIGNAL(setPage(int)),
//                    pages, SLOT(setCurrentIndex(int)));
//            QObject::connect(secondPageWidget, SIGNAL(setPage(int)),
//                    pages, SLOT(setCurrentIndex(int)));
//            QObject::connect(lastPageWidget, SIGNAL(setPage(int)),
//                    pages, SLOT(setCurrentIndex(int)));

            // background changing part
//            QObject::connect(firstPageWidget, SIGNAL(setPage(int)),
//                    this, SLOT(updateBackground(int)));
//            QObject::connect(secondPageWidget, SIGNAL(setPage(int)),
//                    this, SLOT(updateBackground(int)));
//            QObject::connect(secondPageWidget, SIGNAL(setPage(int)),
//                    this, SLOT(updateBackground(int)));
//            QObject::connect(lastPageWidget, SIGNAL(setPage(int)),
//                    this, SLOT(updateBackground(int)));

            // map part
//            QObject::connect(secondPageWidget, SIGNAL(setMapParams(int, const std::vector<std::vector<int>>&)),
//                    lastPageWidget, SLOT(getMapParams(int, const std::vector<std::vector<int>>&)));
        }

        void MainWindow::updateBackground(int){
            QString qstr = ":/fig/terrain.png";
            // change the file directory depending on page number.
//            switch (page_number){
//            case 0:
//                qstr = ":/fig/terrain.png";
//                break;
//            case 1:
//                qstr = ":/fig/page2.jpeg";
//                break;
//            case 2:
//                qstr = ":/fig/page3.jpeg";
//                break;
//            default:
//                qstr = ":/fig/terrain.png";
//                break;
//            }
            // set background.
            QPixmap bkgnd(qstr);
            bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
            QPalette palette;
            palette.setBrush(QPalette::Background, bkgnd);
            setPalette(palette);
            return;
        }
    }

}
