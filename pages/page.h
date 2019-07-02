#ifndef PAGE_H
#define PAGE_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
namespace PTG {
    namespace view {
        /**
         * @brief The Page class is a base class for all other page widgets.
         */
        class Page : public QWidget
        {
            Q_OBJECT
        public:
            /**
             * @brief Page create a new page with a grid layout.
             * @param parent the parent widget for this page.
             */
            explicit Page(QWidget *parent = nullptr);

            /**
             * Virtual destructor
             */
            virtual ~Page() = default;
        private:
            QGridLayout * layout;

        signals:
            /**
             * @brief setPage sets the currently displayed page.
             * @param page_number the index of the page to display.
             */
            void setPage(int page_number);

        public:
            /**
             * @brief This function adds a widget to the page at a given position
             * @param ptrw is the widget we want to add
             * @param row is the row position
             * @param col is the column position
             */
            void addPageWidget(QWidget *ptrw, int row, int col);
            /**
             * @brief This function adds a widget to the page (default)
             * @param ptrw isthe widget we wantt o add
             */
            void addPageWidget(QWidget *ptrw);
            /**
             * @brief This function adds a Layout to the current grid layout at a position
             * @param ptrl is pointer to the new layout
             * @param row is the row position
             * @param col is the column position
             */
            void addLayout(QLayout * ptrl, int row, int col);
            /**
             * @brief Similar to setLayout function in QWidgets, this function sets the main layout
             * to the page widget
             */
            void setPageLayout();
            /**
             * @brief This function merely signifies the re-occurrance of setting page styles to pages
             */
            virtual void setPageStyle();
        };
    }
}
#endif // PAGE_H
