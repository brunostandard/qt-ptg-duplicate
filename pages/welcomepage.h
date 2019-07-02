#ifndef WELCOMEPAGE_H
#define WELCOMEPAGE_H

#include "view/ptgbutton.h"
#include "page.h"
namespace PTG {
    namespace view {
        /**
         * @brief The WelcomePage class is the front page of the application,
         * giving users access to generating/loading terrains, looking at about information, and quiting the application.
         */
        class WelcomePage : public Page
        {
            Q_OBJECT
        public:
            /**
             * @brief WelcomePage construct the welcome page with content, styles, and connections.
             * @param parent
             */
            explicit WelcomePage(QWidget *parent = nullptr);

            /**
             * @brief ~WelcomePage (virtual destructor)
             */
            virtual ~WelcomePage() override;
        private:
            QLabel * title = nullptr;
            QPushButton * newTerrainButton = nullptr;
            QPushButton * aboutButton = nullptr;
            QPushButton * instructButton = nullptr;
            QPushButton * quitButton = nullptr;
            QPushButton * muteButton = nullptr;
            QHBoxLayout * temp_button_row_layout = nullptr;
        public slots:
            /**
             * @brief nextButtonPushed sets the current page to the generation page.
             */
            void nextButtonPushed();

            /**
             * @brief aboutButtonPushed sets the current page to the about page.
             */
            void aboutButtonPushed();

            /**
             * @brief instructButtonPushed sets the current page to the instruction page.
             */
            void instructButtonPushed();

            /**
             * @brief muteButtonPushed mutes the music.
             */
            void muteButtonPushed();

            /**
             * @brief setPageStyle sets the stylesheets and font used in this page.
             */
            void setPageStyle() override;
        signals:
            /**
             * @brief muteButtonClicked mutes the music.
             */
            void muteButtonClicked();

            /**
             * @brief instructButtonClicked sets the current page to the instruction page.
             */
            void instructButtonClicked();
        };
    }
}

#endif // WELCOMEPAGE_H
