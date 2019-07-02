#include "view/ptgbutton.h"

#include <QRandomGenerator64>
#include <QDebug>
namespace PTG{
namespace view{

PTGButton::PTGButton()
{
    _initStyleSheets();
    _initSoundEffects();
    _initConnections();
}

void PTGButton::_playSound()
{
    size_t r = QRandomGenerator64::global()->bounded(0,effects.size());
    effects[r]->play();
    qDebug() << "Play sound from button click.";
}

void PTGButton::_initStyleSheets()
{
    setStyleSheet("font-size: 50px;"
                  "font-variant: small-caps;"
                  "font-weight: bold;"
                  "border-radius: 3px;"
                  "border-color: white;"
                  "background-color: rgba(40,25,20, .6);"
                  "text-align: center;");
}

void PTGButton::_initSoundEffects()
{
    QSoundEffect * se1 = new QSoundEffect();
    se1->setSource(QUrl("qrc:/sounds/click_Ab.wav"));
    effects.push_back(se1);
    QSoundEffect * se2 = new QSoundEffect();
    se2->setSource(QUrl("qrc:/sounds/click_C.wav"));
    effects.push_back(se2);
    QSoundEffect * se3 = new QSoundEffect();
    se3->setSource(QUrl("qrc:/sounds/click_Eb.wav"));
    effects.push_back(se3);
    QSoundEffect * se4 = new QSoundEffect();
    se4->setSource(QUrl("qrc:/sounds/click_G.wav"));
    effects.push_back(se4);

    for(auto & effect: effects){
        effect->setVolume(2.0);
    }
}

void PTGButton::_initConnections()
{
    connect(this, SIGNAL(clicked()), this, SLOT(_playSound()));
}

}
}
