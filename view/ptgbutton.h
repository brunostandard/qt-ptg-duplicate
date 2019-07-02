#ifndef PTGBUTTON_H
#define PTGBUTTON_H

#include <vector>

#include <QPushButton>
#include <QtMultimedia/QSoundEffect>


namespace PTG{
namespace view{
/**
 * @brief The ptgButton class encapsulates sound effects and styles used in ptg buttons.
 */
class PTGButton : public QPushButton
{

    Q_OBJECT

public:
    /**
     * @brief PTGButton constructs a button with styles, fonts, and sound effects.
     */
    PTGButton();

private slots:
    /**
     * @brief _playSound plays a random sound effect from the member effects.
     */
    void _playSound();

private:
    /**
    * @brief _initStyleSheets initializes stylesheet for this button.
    */
   void _initStyleSheets();

   /**
    * @brief _initSoundEffects loads sound effects into member effects.
    */
   void _initSoundEffects();

   /**
   * @brief _initStyleSheets initializes connections for this button.
   */
   void _initConnections();

   std::vector<QSoundEffect*> effects;
};
}
}

#endif // PTGBUTTON_H
