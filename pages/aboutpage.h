#ifndef ABOUTPAGE_H
#define ABOUTPAGE_H

#include <QWidget>
#include "page.h"

namespace PTG {
    namespace view {
        class AboutPage : public Page
        {
            Q_OBJECT
        public:
            explicit AboutPage(QWidget *parent = nullptr);

            ~AboutPage() override;
        private:
            QLabel * description = nullptr;
            QLabel * title = nullptr;
            QPushButton * button = nullptr;

        public slots:
            void buttonPushed();
            void setPageStyle() override;
        };
    }
}

#endif // ABOUTPAGE_H
