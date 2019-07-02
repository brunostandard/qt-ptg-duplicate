#include "page.h"
#include <QDebug>
#include <QFontDatabase>

namespace PTG {
    namespace view {
        Page::Page(QWidget *parent) : QWidget(parent),
            layout(new QGridLayout)
        {
            qDebug() << "Page()";
        }

        void Page::addPageWidget(QWidget *ptrw, int row, int col) {
            layout->addWidget(ptrw,row,col);
        }
        void Page::addPageWidget(QWidget *ptrw){
            layout->addWidget(ptrw);
        }
        void Page::addLayout(QLayout * ptrl, int row, int col){
            layout->addLayout(ptrl, row, col);
        }
        void Page::setPageLayout(){
            setLayout(layout);
        }
        void Page::setPageStyle(){
            this->setStyleSheet("border: 5px solid white;"
                              "color: white;"
                              "font: 'Times New Roman';"
                              "font-size: 42px;"
                              "border-radius: 4px;"
                              "padding: 5px;"
                              "text-align: center;"
                              "background-color: rgba(40,25,20, .6);");

        }
    }
}
