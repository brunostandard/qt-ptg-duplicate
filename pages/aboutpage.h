#ifndef ABOUTPAGE_H
#define ABOUTPAGE_H

#include <QWidget>
#include "page.h"

namespace PTG {
    namespace view {
        /**
         * @brief The AboutPage class displays an overview of the project, as well as
         * the licenses of 3rd-party code and resources.
         */
        class AboutPage : public Page
        {
            Q_OBJECT
        public:
            /**
             * @brief AboutPage initializes the content and styles of an about page.
             * @param parent the parent QWidget to use.
             */
            explicit AboutPage(QWidget *parent = nullptr);

            /**
             * @brief ~AboutPage (virtual destructor)
             */
            virtual ~AboutPage() override;
        private:
            QLabel * description = nullptr;
            QLabel * title = nullptr;
            QPushButton * backButton = nullptr;

        public slots:
            /**
             * @brief backButtonPushed sets the page back to the welcome page.
             */
            void backButtonPushed();

            /**
             * @brief setPageStyle initializes the stylesheet and font to use for this page.
             */
            void setPageStyle() override;
        };
    }
}

#endif // ABOUTPAGE_H
