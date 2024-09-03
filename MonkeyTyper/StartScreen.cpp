#include <iostream>
#include <fstream>
#include <fmt/core.h>
#include <SFML/Graphics.hpp>

class StartScreen {

private:

    sf::RenderWindow& window;
    sf::Texture textureStart;

public:

    StartScreen(sf::RenderWindow& window)
    : window(window) {

        if (!textureStart.loadFromFile("../MyImages/START.png")) {
            fmt::println("Error - loading START");
        }

    }



    auto play() -> void {

        sf::Sprite startScreen(textureStart);

        window.setFramerateLimit(60);

        while(window.isOpen()){

            for (auto event = sf::Event(); window.pollEvent(event);) {

                if (event.type == sf::Event::Closed) {
                    window.close();
                }

            }

            startScreen.move(-4.f, 0.f);

            if (startScreen.getPosition().x < -2600.f) {
                return;
            }


            window.clear(sf::Color::Black);

            window.draw(startScreen);

            window.display();

        }

    }

};
