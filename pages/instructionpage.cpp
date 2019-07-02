#include "instructionpage.h"
#include "instructionpage.h"
#include <QDebug>
#include <QFontDatabase>
#include "view/ptgbutton.h"

namespace PTG {
    namespace view {
        InstructionPage::InstructionPage(QWidget * parent) : Page(parent),
            descriptionPart1(new QLabel),
            descriptionPart2(new QLabel),
            description_holder_row_layout(new QHBoxLayout),
            title(new QLabel),
            backButton(new PTGButton)
        {
            qDebug() << "InstructionPage()";

            // adding a QPixmap to the description lables
            QString str1 = ":/fig/instruction_image_page1.png"; // first page of instructions
            QString str2 = ":/fig/instruction_image_page2.png"; // second page
            descriptionPixmap1 = QPixmap(str1);
            descriptionPixmap2 = QPixmap(str2);
            descriptionPart1->setPixmap(descriptionPixmap1); // add pixmap
            descriptionPart2->setPixmap(descriptionPixmap2); // add pixmap
            descriptionPart1->hide(); // hide the image, otherwise it would make the window too big
            descriptionPart2->hide(); // hide the image
            description_holder_row_layout->addWidget(descriptionPart1);  // add first page to row layout
            description_holder_row_layout->addWidget(descriptionPart2); // add second page to row layout

            title->setText("Instructions"); // set title
            title->setAlignment(Qt::AlignCenter); // make sure it's centered
            backButton->setText("Back"); // set back button text

            addPageWidget(title); // first add the title of the page
            addLayout(description_holder_row_layout,1,0); // add the layout holding the two page images.
            addPageWidget(backButton);

            setPageLayout(); // done, set the (page) layout

            QObject::connect(backButton,SIGNAL(clicked()),this,SLOT(backButtonPushed())); // connect the back button,
                        // this is to swap pages and to call the instructionPageNotInView() function

            setPageStyle();
        }
        InstructionPage::~InstructionPage() {

        }
        void InstructionPage::instructionPageInView() {
            descriptionPart1->show(); // show the images (i.e pages).
            descriptionPart2->show();
        }
        void InstructionPage::instructionPageNotInView() {
            qDebug() << "InstructionPage::instructionPageNotInView()";
            descriptionPart1->hide(); // hide the images. otherwise, window will be too big
            descriptionPart2->hide();
        }
        void InstructionPage::backButtonPushed() {
            qDebug() << "about page backButton pushed";
            instructionPageNotInView(); // hide the images.
            emit Page::setPage(0);
        }
        void InstructionPage::setPageStyle() {
            Page::setPageStyle(); // add page style, but we are going to add more ...
            title->setStyleSheet("color: white;"
                              "font-size: 111px;"
                              "font-variant: small-caps;"
                              "font-weight: bold;"
                              "border-radius: 5px;"
                              "padding: 2px;"
                              "text-align: center;");

            if(QFontDatabase::addApplicationFont(":/font/monogram.ttf"))
                qDebug("font loaded");
            // give everything the monogram text font
            QFont monogram("monogram");
            title->setFont(monogram);
            backButton->setFont(monogram);
        }
    }
}
