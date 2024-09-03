#include <fmt/core.h>
#include <SFML/Graphics.hpp>
#include "GeneralSettings.h"

class ExitMenuState {

    sf::RenderWindow& window;
    sf::Texture textureExitMenu;

public:

    ExitMenuState(sf::RenderWindow& window)
            : window(window) {

        if (!textureExitMenu.loadFromFile("../MyImages/EXIT_MENU.png")) {
            fmt::println("Error - loading exit menu");
        }

    }


    auto play() -> void {

        auto exitMenu = sf::Sprite(textureExitMenu);


        window.setFramerateLimit(60);

        while (window.isOpen()) {

            for (auto event = sf::Event(); window.pollEvent(event);) {

                if (event.type == sf::Event::Closed) {
                    window.close();
                }

                if (event.type == sf::Event::MouseButtonPressed) {

                    //EXIT
                    if(event.mouseButton.x >= 463.1f && event.mouseButton.x <= 722.7f && event.mouseButton.y >= 299.f && event.mouseButton.y <= 393.6f){
                        backupGame.setInitialized(false);
                        gameState = GameState::MENU;
                        return;
                    }

                    //SAVE & EXIT
                    if(event.mouseButton.x >= 426.5f && event.mouseButton.x <= 758.2f && event.mouseButton.y >= 411.6f && event.mouseButton.y <= 509.7f){
                        backupGame.setInitialized(true);
                        gameState = GameState::MENU;
                        return;
                    }

                }
            }

            window.clear(sf::Color::Black);

            window.draw(exitMenu);

            window.display();

        }

    }

};
