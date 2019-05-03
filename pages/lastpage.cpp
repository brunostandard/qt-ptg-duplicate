#include "lastpage.h"
#include <QDebug>

namespace PTG {
    namespace view {
        LastPage::LastPage(QWidget *parent) : Page(parent),
            button(new QPushButton),

            myParticle(new Particle(this,this))
        {
            qDebug() << "LastPage()\n";

            button->setText("Back");

            addPageWidget(myParticle);

            addPageWidget(button);

            setPageLayout();

            QObject::connect(button,SIGNAL(clicked()),this,SLOT(buttonPushed()));

            setPageStyle();
        }

        void LastPage::buttonPushed(){
            qDebug() << "Last page button pushed\n";
            emit Page::setPage(1);
        }

        void LastPage::setPageStyle(){

        }

        void LastPage::getMapParams(int k,const std::vector<std::vector<int>>& _map){
            qDebug() << "getMapParams(..): ";
            myParticle->seaLevel = k;
            qDebug() << k << "\n";
            myParticle->map = std::move(_map);
            //_map is now unusuable => the object that made the map has no matrix???
        }
//////////////////////////////////////////////////////////////////////
        LastPage::Particle::Particle(QWidget *parent, LastPage * _container)
            : QLabel(parent),
              container(_container),
              seaLevel(0),
              map(0,std::vector<int>(0))
        {
            qDebug() << "Particle()\n";
        }

        LastPage::Particle::~Particle(){
        }

        void LastPage::Particle::paintEvent(QPaintEvent *) {
            qDebug() << "start of paintEvent()\n";
            QPainter painter;
            painter.begin(this);
            int resolution = 1;

            QColor color = Qt::GlobalColor::darkGreen;

            for (std::size_t x = 0; x <= map.size()-1; ++x) {
                for (std::size_t y = 0; y <= map.size()-1; ++y) {
                    if (map[x][y] <= seaLevel){
                        if (map[x][y] <= seaLevel-50){
                            if (map[x][y] <= seaLevel-120){
                                painter.fillRect(x*resolution,y*resolution,
                                         resolution,resolution,Qt::black);
                            }
                            else {
                                painter.fillRect(x*resolution,y*resolution,
                                         resolution,resolution,Qt::darkBlue);
                            }
                        }
                        else{
                            painter.fillRect(x*resolution,y*resolution,
                                         resolution,resolution,Qt::blue);
                        }
                    }
                    else if (map[x][y] >= seaLevel+100) {
                        painter.fillRect(x*resolution,y*resolution,
                                         resolution,resolution,Qt::GlobalColor::darkGray);
                    }
                    else {
                        painter.fillRect(x*resolution,y*resolution,
                                         resolution,resolution,color);
                    }
                }
            }
            painter.end();
            qDebug() << "end of paintEvent()\n";
         }
    }
}
