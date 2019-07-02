#ifndef INSTRUCTIONPAGE_H
#define INSTRUCTIONPAGE_H

#include "page.h"
#include <QPixmap>
//#include <QScrollArea>
namespace PTG {
namespace view {
/**
 * @brief The InstructionPage class displays an instructions for using the project.
 */
class InstructionPage : public Page
{
    Q_OBJECT
public:
    /*
     * Creates an instruction page with the appropriate content and styles.
     */
    explicit InstructionPage(QWidget *parent = nullptr);

    virtual ~InstructionPage() override;
private:
    QLabel * descriptionPart1 = nullptr; // widget to hold the first page
    QLabel * descriptionPart2 = nullptr; // widget to hold the second page
    QPixmap descriptionPixmap1; // the pixmap that will hold the first page of the instructions
    QPixmap descriptionPixmap2; // the pixmap that will hold the second page of the instructions
    QHBoxLayout * description_holder_row_layout = nullptr; // a layout to hold pages in a row
    QLabel * title = nullptr; // the title
    QPushButton * backButton = nullptr; // back button

    /**
      This function simply hides the description pixmap images from view provided that the user is
      exiting the instructions page via the back button.
    */
    void instructionPageNotInView();

public slots:
    /**
     * @brief backButtonPushed changes the current page to the welcome page.
     */
    void backButtonPushed();
    /**
     * @brief instructionPageInView toggles visibility of the instruction image.
     */
    void instructionPageInView();
    /**
     * @brief setPageStyle initializes the stylesheets and fonts for this page.
     */
    void setPageStyle() override;
};
}
}


#endif // INSTRUCTIONPAGE_H
