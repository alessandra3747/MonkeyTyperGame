#include <SFML/Graphics.hpp>
#include "GeneralSettings.h"
#include "SettingsScreen.h"

class DifficultyState : public SettingsScreen{


public:

    DifficultyState(sf::RenderWindow& window)
    : SettingsScreen(window, "../MyImages/DIFFICULTIES.png", "../MyImages/DifficultyButtonPressed.png") { }



    auto inWhichDiffButton(sf::Event::MouseButtonEvent const& mouse) -> DifficultyLevel {

        if(mouse.x >= 384.1f && mouse.x <= 827.4f && mouse.y >= 182.f && mouse.y <= 313.6f) {
            buttonPressed.setPosition(384.1f, 182.f);
            drawButtonPressed = true;
            return DifficultyLevel::EASY;
        }
        if(mouse.x >= 384.1f && mouse.x <= 827.4f && mouse.y >= 360.6f && mouse.y <= 492.1f) {
            buttonPressed.setPosition(384.1f, 360.6f);
            drawButtonPressed = true;
            return DifficultyLevel::MEDIUM;
        }
        if(mouse.x >= 384.1f && mouse.x <= 827.4f && mouse.y >= 541.1f && mouse.y <= 672.7f) {
            buttonPressed.setPosition(384.1f, 541.1f);
            drawButtonPressed = true;
            return DifficultyLevel::HARD;
        }

        return difficultyLevel;
    }


    auto virtual componentFunction(sf::Event::MouseButtonEvent const& mouse) -> void {
        changeDifficulty(inWhichDiffButton(mouse));
    }


};