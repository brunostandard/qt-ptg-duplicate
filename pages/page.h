#ifndef PAGE_H
#define PAGE_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
namespace PTG {
    namespace view {
        class Page : public QWidget
        {
            Q_OBJECT
        public:
            explicit Page(QWidget *parent = nullptr);
            virtual ~Page() = default;
        private:
            QGridLayout * layout;

        signals:
            void setPage(int);

        public:
            void addPageWidget(QWidget *ptrw, int row, int col);
            void addPageWidget(QWidget *ptrw);
            void addLayout(QLayout * ptrl, int row, int col);
            void setPageLayout();
            virtual void setPageStyle();
        };
    }
}
#endif // PAGE_H
