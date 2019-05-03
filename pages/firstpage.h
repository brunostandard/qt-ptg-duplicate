#ifndef FIRSTPAGE_H
#define FIRSTPAGE_H

#include "page.h"
namespace PTG {
    namespace view {
        class FirstPage : public Page
        {
            Q_OBJECT
        public:
            explicit FirstPage(QWidget *parent = nullptr);

        private:
            QLabel * message = nullptr;
            QLabel * title = nullptr;
            QPushButton * button = nullptr;

        public slots:
            void buttonPushed();
            void setPageStyle() override;
        };
    }
}

#endif // FIRSTPAGE_H
