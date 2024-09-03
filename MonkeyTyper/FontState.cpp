#include <SFML/Graphics.hpp>
#include "GeneralSettings.h"
#include "SettingsScreen.h"

class FontState : public SettingsScreen{

public:

    FontState(sf::RenderWindow& window)
    : SettingsScreen(window, "../MyImages/FONTS.png", "../MyImages/ButtonPressed.png") { }



    auto inWhichFontButton(sf::Event::MouseButtonEvent const& mouse) -> FontType{

        if(mouse.x >= 74.8f && mouse.x <= 510.9f && mouse.y >= 196.7f && mouse.y <= 328.8f) {
            buttonPressed.setPosition(74.8f, 196.7f);
            drawButtonPressed = true;
            return FontType::JOSEFINSANS;
        }
        if(mouse.x >= 74.8f && mouse.x <= 510.9f && mouse.y >= 380.8f && mouse.y <= 512.8f) {
            buttonPressed.setPosition(74.8f, 380.8f);
            drawButtonPressed = true;
            return FontType::OPENSANS;
        }
        if(mouse.x >= 74.8f && mouse.x <= 510.9f && mouse.y >= 564.8f && mouse.y <= 696.8f) {
            buttonPressed.setPosition(74.8f, 564.8f);
            drawButtonPressed = true;
            return FontType::ORBITRON;
        }
        if(mouse.x >= 682.9f && mouse.x <= 1116.9f && mouse.y >= 196.7f && mouse.y <= 328.8f) {
            buttonPressed.setPosition(682.9f, 196.7f);
            drawButtonPressed = true;
            return FontType::OSWALD;
        }
        if(mouse.x >= 682.9f && mouse.x <= 1116.9f && mouse.y >= 380.8f && mouse.y <= 512.8f) {
            buttonPressed.setPosition(682.9f, 380.8f);
            drawButtonPressed = true;
            return FontType::ROBOTOMONO;
        }
        if(mouse.x >= 682.9f && mouse.x <= 1116.9f && mouse.y >= 564.8f && mouse.y <= 696.8f) {
            buttonPressed.setPosition(682.9f, 564.8f);
            drawButtonPressed = true;
            return FontType::TEKO;
        }

        return currentFontType;
    }


    auto virtual componentFunction(sf::Event::MouseButtonEvent const& mouse) -> void {
        changeFont(inWhichFontButton(mouse));
    }

};