#pragma once
#include <fmt/core.h>
#include <SFML/Graphics.hpp>
#include "GeneralSettings.h"

class SettingsScreen{

protected:

    std::string backgroundImagePath;
    std::string buttonPressedImagePath;

    sf::RenderWindow& window;
    sf::Texture textureBackground;

    sf::Texture textureButtonPressed;
    sf::Sprite buttonPressed;
    bool drawButtonPressed;

public:

    SettingsScreen(sf::RenderWindow& window, const std::string& backgroundImagePath, const std::string& buttonPressedImagePath )
            : window(window), backgroundImagePath(backgroundImagePath), buttonPressedImagePath(buttonPressedImagePath) {

        if (!textureBackground.loadFromFile(backgroundImagePath)) {
            fmt::println("Error - loading background");
        }
        if (!textureButtonPressed.loadFromFile(buttonPressedImagePath)) {
            fmt::println("Error - loading textureButtonPressed");
        }

        buttonPressed.setTexture(textureButtonPressed);

        drawButtonPressed = false;

    }


    virtual auto isMenuButtonPressed(sf::Event::MouseButtonEvent const& mouse) -> bool {
        return mouse.x >= 488 && mouse.x <= 692 && mouse.y >= 714 && mouse.y <= 770;
    }

    virtual auto componentFunction(sf::Event::MouseButtonEvent const& mouse) -> void = 0;


    virtual auto play() -> void {

        auto screen = sf::Sprite(textureBackground);

        while (window.isOpen()) {

            for (auto event = sf::Event(); window.pollEvent(event);) {

                if (event.type == sf::Event::Closed) {
                    window.close();
                    return;
                }

                if(event.type == sf::Event::MouseButtonPressed){

                    if(isMenuButtonPressed(event.mouseButton)){
                        gameState = GameState::MENU;
                        return;
                    }

                    componentFunction(event.mouseButton);

                }

            }

            if(drawButtonPressed) {

                window.draw(buttonPressed);

                window.display();

                sf::sleep(sf::seconds(0.1));

                drawButtonPressed = false;
            }

            window.clear(sf::Color::Black);

            window.draw(screen);

            window.display();

        }
    }

};