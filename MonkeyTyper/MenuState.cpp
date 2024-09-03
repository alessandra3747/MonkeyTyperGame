#include <SFML/Graphics.hpp>
#include "GeneralSettings.h"
#include "ScoreBoard.h"


class MenuState{

    sf::RenderWindow& window;
    ScoreBoard& scoreBoard;
    sf::Texture textureBackground;

public:

    MenuState(sf::RenderWindow& window, ScoreBoard& scoreBoard)
    : window(window), scoreBoard(scoreBoard){

        if (!textureBackground.loadFromFile("../MyImages/MENU.png")) {
            fmt::println("Error - loading background");
        }

    }


    auto inWhichButton(sf::Event::MouseButtonEvent const& mouse) -> GameState {

        if(mouse.x >= 300 && mouse.x <= 910 && mouse.y >= 75 && mouse.y <= 260)
            return GameState::PLAYING;
        if(mouse.x >= 300 && mouse.x <= 910 && mouse.y >= 303 && mouse.y <= 487)
            return GameState::DIFFICULTY;
        if(mouse.x >= 300 && mouse.x <= 910 && mouse.y >= 533 && mouse.y <= 716)
            return GameState::FONT;
        if(mouse.x >= 1000.f && mouse.x <= 1180.f && mouse.y >= 21.f && mouse.y <= 83.f)
            return GameState::EXIT;

        return GameState::MENU;

    }


    auto play() -> void {

        auto menuScreen = sf::Sprite(textureBackground);

        window.setFramerateLimit(60);

        while (window.isOpen()) {

            for (auto event = sf::Event(); window.pollEvent(event);) {

                if (event.type == sf::Event::Closed) {
                    window.close();
                }

                if(event.type == sf::Event::MouseButtonPressed){

                    switch(inWhichButton(event.mouseButton)) {
                        case GameState::DIFFICULTY:
                            gameState = GameState::DIFFICULTY;
                            return;
                        case GameState::FONT:
                            gameState = GameState::FONT;
                            return;
                        case GameState::PLAYING:
                            gameState = GameState::PLAYING;
                            return;
                        case GameState::EXIT:
                            gameState = GameState::EXIT;
                            return;
                        default:
                            gameState = GameState::MENU;
                    }

                }

            }

            window.clear(sf::Color::Black);

            window.draw(menuScreen);

            scoreBoard.drawScoreBoard(window);

            window.display();

        }
    }

};