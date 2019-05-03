#ifndef LASTPAGE_H
#define LASTPAGE_H

#include "page.h"
#include <QPixmap>
#include <QRect>
#include <QPainter>
namespace PTG {
    namespace view {
        class LastPage : public Page
        {
            Q_OBJECT
        public:

            explicit LastPage(QWidget *parent = nullptr);

        private:

            QPushButton * button = nullptr;

            class Particle;

            Particle * myParticle = nullptr;

        public slots:

            void buttonPushed();

            void setPageStyle() override;

            void getMapParams(int, const std::vector<std::vector<int>>&);

        };

        class LastPage::Particle : public QLabel{
            Q_OBJECT
        public:
            friend class LastPage;

            Particle(QWidget *parent = nullptr, LastPage * _container = nullptr);

            ~Particle() override;

            void paintEvent(QPaintEvent * q) override;
        private:
            LastPage * const container;
            int seaLevel = 0;
            std::vector<std::vector<int>> map;

        };
    }
}
#endif // LASTPAGE_H
