#include "terrainpage.h"
#include <QDebug>
#include <QFontDatabase>
#include "view/ptgbutton.h"
#include <QVBoxLayout>
#include <QGraphicsPixmapItem>
#include <QRandomGenerator>
#include <vector>
#include <QFileDialog>


namespace PTG {
    namespace view {
        TerrainPage::TerrainPage(QWidget *parent) : Page(parent),
            backButton(new PTGButton),
            legendButton(new PTGButton),
            legendTable(new QLabel(this)),
            image(new TerrainView(this))
        {
            qDebug() << "LastPage()";
            backButton->setText("Back"); // set back button text
            QString file_name = ":/fig/legend_table.png";
            legendPixmapTable = QPixmap(file_name); // add pixmap to legend label
            legendTable->setPixmap(legendPixmapTable); // add it
            legendButton->setText("Legends"); // set text for the legend button
            tools = new TerrainTools(); // the tools: export, zoom-in, and zoom-out buttons
            addPageWidget(tools,0,0);
            addPageWidget(image,0,1); // the terrain image (completed)
            addPageWidget(backButton,1,0);
            addPageWidget(legendButton,1,2);
            addPageWidget(legendTable,0,2);

            setPageLayout(); // done, set the (page) layout
            legendTable->hide(); // hide the pixmap initially, and open when called

            PTGButton * exButton = tools->getExportButton();
            PTGButton * zinButton = tools->getZoomInButton();
            PTGButton * zoutButton = tools->getZoomOutButton();

            // setting the connections
            // if back button is clicked, call back button pushed to take us to generation page
            QObject::connect(backButton,SIGNAL(clicked()),this,SLOT(backButtonPushed()));
            // if legend button pushed, call the legend button pushed function to show the legend pixmap table
            QObject::connect(legendButton,SIGNAL(clicked()),this,SLOT(legendButtonPushed()));
            // if the export button is clicked, call the export PNG function
            QObject::connect( exButton, SIGNAL(clicked()),
                              this, SLOT(exportPNG()));
            // zoom in and zoom out connections:
            QObject::connect(zinButton, SIGNAL(clicked()),
                             this, SLOT(zoomIn()));
            QObject::connect(zoutButton, SIGNAL(clicked()),
                             this, SLOT(zoomOut()));

            setPageStyle();
        }

        TerrainPage::~TerrainPage()
        {

        }

        void TerrainPage::backButtonPushed(){
            qDebug() << "TerrainPage::backButtonPushed()";

            emit Page::setPage(1);
        }
        void TerrainPage::legendButtonPushed() {
            static bool open = false; // assume that the table isn't in view
            qDebug() << "TerrainPage::legendButtonPushed()" << open;
            if (open) { // if image is open and in view,
                legendTable->hide(); // hide the image
                legendButton->setText("Legends"); // re-name the button
                open = false; // now the image is hidden
            }
            else { // the image is not open nor in view
                legendTable->show(); // show it
                legendButton->setText("hide"); // re-nname the button text
                open = true; // now the image is open.
            }
        }

        void TerrainPage::setPageStyle() {
            //Page::setPageStyle();

            this->setStyleSheet("border: 5px solid white;"
                              "color: white;"
                              "font-size: 111px;"
                              "font-variant: small-caps;"
                              "font-weight: bold;"
                              "border-radius: 5px;"
                              "border-color: white;"
                              "padding: 2px;"
                              "text-align: center;");

            if(QFontDatabase::addApplicationFont(":/font/monogram.ttf"))
                qDebug("font loaded");
            QFont monogram("monogram");
            this->setFont(monogram);
            backButton->setFont(monogram);
            legendButton->setFont(monogram);
        }

        void TerrainPage::getMapParams(data::DiamondSquare obj, int j, int k, int l){
            data::TerrainData obj2(obj,j,k,l); // make a new terrain data object
            qDebug() << j << " " << k << " " << l;
            image->clearScence(); // clear what was in the scence
            image->printScence(obj2); // re-print the image with the most update terrain data
        }

        void TerrainPage::zoomIn(){
            int currentZoom = image->getZoom();
            // Check for max zoom out
            if(currentZoom >= 2){
                return; //don't do anything
            }
            else{
                qDebug() << "Setting zoom to level " << currentZoom + 1;
                this->image->setZoom(currentZoom+1);
            }
        }


        void TerrainPage::zoomOut(){
            int currentZoom = image->getZoom();
            // Check for max zoom out
            if(currentZoom <= -2){
                return; //don't do anything
            }
            else{
                qDebug() << "Setting zoom to level " << currentZoom - 1;
                this->image->setZoom(currentZoom-1);
            }
        }


        void TerrainPage::exportPNG()
        {
            QString path = QFileDialog::getSaveFileName(this,
                                                        tr("Export Image"),
                                                        tr("terrain_export.png"));
            // If path is blank, then return without saving.
            if(path == "" || path ==  NULL){
                return;
            }
            float scale = 1.0;

            image->exportPNG(path, scale);
            qDebug() << "Exported .png to " << path << " at scale " << scale;
        }

    }
}
