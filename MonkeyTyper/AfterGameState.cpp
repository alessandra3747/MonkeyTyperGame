#include <SFML/Graphics.hpp>
#include <fmt/core.h>
#include "GeneralSettings.h"

class AfterGameState {

    sf::RenderWindow& window;
    sf::Texture textureAfterGameWindow;
    sf::Font scoreFontType;

public:

    AfterGameState(sf::RenderWindow& window)
            : window(window) {

        if(gameState == GameState::GAMEOVER) {

            if (std::stoi(score) > highScore) {
                if (!textureAfterGameWindow.loadFromFile("../MyImages/H_GAMEOVER.png")) {
                    fmt::println("Error - loading background");
                }
            } else {
                if (!textureAfterGameWindow.loadFromFile("../MyImages/NOH_GAMEOVER.png")) {
                    fmt::println("Error - loading background");
                }
            }

        } else if (gameState == GameState::WIN){

            if (!textureAfterGameWindow.loadFromFile("../MyImages/MaxWordsReached.png")) {
                fmt::println("Error - loading background");
            }

        }

        if (!scoreFontType.loadFromFile("../MyFonts/JaroFont.ttf"))
            fmt::println("Error - loading font in GameOver from file");

    }


    auto play() -> void {

        auto afterGameWindow = sf::Sprite(textureAfterGameWindow);


        auto scoreToShow = getText(26);
        scoreToShow.setFillColor(sf::Color(248,46,255));

        scoreToShow.setString(score);
        scoreToShow.setPosition( 573.f, 370.f );
        scoreToShow.setFont(scoreFontType);


        window.setFramerateLimit(60);

        while (window.isOpen()) {

            for (auto event = sf::Event(); window.pollEvent(event);) {

                if (event.type == sf::Event::Closed) {
                    window.close();
                }

                if (event.type == sf::Event::MouseButtonPressed) {

                    switch (inWhichButton(event.mouseButton)) {
                        case GameState::PLAYING:
                            gameState = GameState::PLAYING;
                            return;
                        case GameState::MENU:
                            gameState = GameState::MENU;
                            return;
                        default:
                            gameState = GameState::GAMEOVER;
                    }

                }
            }

            window.clear(sf::Color::Black);

            window.draw(afterGameWindow);

            window.draw(scoreToShow);

            window.display();

        }

    }

    auto inWhichButton(sf::Event::MouseButtonEvent const& mouse) -> GameState{

        if(mouse.x >= 380.f && mouse.x <= 574.f && mouse.y >= 430.4f && mouse.y <= 495.f)
            return GameState::MENU;
        if(mouse.x >= 617.f && mouse.x <= 810.f && mouse.y >= 430.4f && mouse.y <= 495.f)
            return GameState::PLAYING;

        return GameState::GAMEOVER;
    }

};
