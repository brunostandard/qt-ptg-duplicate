#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QStackedWidget>
#include "pages/firstpage.h"
//#include "pages/secondpage.h"
//#include "pages/lastpage.h"
//#include "pages/aboutpage.h"
//#include <QComboBox>
namespace PTG {
    namespace view {
        class MainWindow : public QWidget
        {
            Q_OBJECT

        public:


            /**
                Constructor.
                @param parent is the widget that will take ownership of MainWindow.
            */
            MainWindow(QWidget *parent = nullptr);


            /**
                Destructor
            */
            ~MainWindow();

        private:
//            QStackedWidget * pages = nullptr;

            QVBoxLayout * main_layout = nullptr;
            Page * firstPageWidget = nullptr;
//            Page * secondPageWidget = nullptr;
//            Page * lastPageWidget = nullptr;
//            Page * aboutPageWidget = nullptr;
//            QComboBox * pageComboBox = nullptr;


            /**
                This function marks each page in the stackedwidget calleed pages.
            */
            void markPages();


            /**
                This funciton initializes the pages in a certain order (order doesn't matter)
            */
            void setStackedPages();


            /**
                This function sets the connections between buttons and other functions; All
                connections we be made here for simplicity.
            */
            void setConnections();


            /**
                This function sets the background of MainWindow depending on the current page
                begin displayed.
            */
            void setBackground();
        public slots:


            /**
                This function will take in a signal an integer; depending on the value of
                page_number, the correct background will be called.
            */
            void updateBackground(int page_number);


        };
    }
}
#endif // MAINWINDOW_H
