#include <fmt/core.h>
#include <SFML/Graphics.hpp>
#include "GeneralSettings.h"
#include "ScoreBoard.h"

class GameplayState{

    sf::RenderWindow& window;
    ScoreBoard& scoreBoard;
    sf::Texture textureBackground;

public:

    GameplayState(sf::RenderWindow& window, ScoreBoard& scoreBoard)
            : window(window), scoreBoard(scoreBoard) {

        if (!textureBackground.loadFromFile("../MyImages/MyBackground.png")) {
            fmt::println("Error - loading background");
        }

    }


    auto play() -> void {

        resetSettings();

        auto background = sf::Sprite(textureBackground);


        auto infoPanel = getRectanglePanel();


        auto words = std::vector<sf::Text>();
        auto wordCounter = 0;

        if(backupGame.getIsInitialized()) {
            words = backupGame.getPrevWords();
            wordCounter = backupGame.getPrevWordCounter();
            lifesAmount = backupGame.getLifeAmount();
            score = backupGame.getPrevScore();

            backupGame.setInitialized(false);
        }



        auto scoreText = getText(30);
        scoreText.setString(score);
        scoreText.setPosition(1050.f, infoPanel.getPosition().y + 30.f);


        maxWordAmount = setMaxWordAmount();

        auto wordCountText = getText(25);

        wordCountText.setString(std::to_string(wordCounter));
        wordCountText.setPosition(485.f, infoPanel.getPosition().y + 40.f);

        auto wordLimit = getText(25);
        wordLimit.setString(" / " + std::to_string(maxWordAmount));
        wordLimit.setPosition(515.f, infoPanel.getPosition().y + 40.f);



        auto playerInput = sf::String();
        auto playerText = getText(30);

        playerText.setString("");
        playerText.setPosition(20.f, infoPanel.getPosition().y + 20.f);



        auto textureLife = sf::Texture();
        if (!textureLife.loadFromFile("../MyImages/heart.png")) {
            fmt::println("Error - loading textureLife");
        }
        auto life = sf::Sprite(textureLife);


        auto textureMenuIcon = sf::Texture();
        if (!textureMenuIcon.loadFromFile("../MyImages/MENUICON.png")) {
            fmt::println("Error - loading MenuIcon");
        }
        auto menuIcon = sf::Sprite(textureMenuIcon);
        menuIcon.setPosition(1026.f, 21.f);



        auto clock = sf::Clock();


        auto gameSpeed = int();

        switch (difficultyLevel) {
            case DifficultyLevel::MEDIUM:
                gameSpeed = 80;
                break;
            case DifficultyLevel::HARD:
                gameSpeed = 100;
                break;
            default:
                gameSpeed = 60;
        }


        window.setFramerateLimit(gameSpeed);

        while (window.isOpen()) {

            if (lifesAmount == 0) {
                gameState = GameState::GAMEOVER;
                scoreBoard.addScore(std::stoi(score));
                return;
            }
            if (wordCounter == maxWordAmount) {
                gameState = GameState::WIN;
                scoreBoard.addScore(std::stoi(score));
                return;
            }

            for (auto event = sf::Event(); window.pollEvent(event);) {

                if (event.type == sf::Event::Closed) {
                    window.close();
                }

                if (event.type == sf::Event::KeyPressed) {

                    if (event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Space) {

                        for (auto &word: words) {

                            if (word.getString() == playerInput) {

                                auto tmpScore = std::stoi(score);

                                switch (difficultyLevel) {
                                    case DifficultyLevel::MEDIUM:
                                        tmpScore += 150;
                                        break;
                                    case DifficultyLevel::HARD:
                                        tmpScore += 200;
                                        break;
                                    default:
                                        tmpScore += 100;
                                }

                                score = std::to_string(tmpScore);

                                scoreText.setString(score);

                                word.setString(chooseTextValue());
                                word.setPosition(-100.f, infoPanel.getPosition().y - 20.f - std::rand() % 650);

                                if(difficultyLevel == DifficultyLevel::HARD) {
                                    auto rotationAngle = -30 + std::rand() % 60;
                                    word.setRotation(rotationAngle);
                                }

                                wordCounter++;

                                wordCountText.setString(std::to_string(wordCounter));

                            }

                        }

                        playerInput.clear();
                        playerText.setString("");

                    }

                    if (event.key.scancode == sf::Keyboard::Scan::Backspace) {
                        if (playerInput.isEmpty())
                            continue;

                        playerInput.erase(playerInput.getSize() - 1, 1);
                        playerText.setString(playerInput);

                    }

                }

                if (event.type == sf::Event::TextEntered) {

                    if (event.text.unicode == '\n' || event.text.unicode == ' ' || event.text.unicode == '\b')
                        continue;

                    if (playerInput.getSize() < 15) {

                        playerInput += event.text.unicode;
                        playerText.setString(playerInput);

                    }

                }

                if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.x >= 1026.f && event.mouseButton.x <= 1178.f && event.mouseButton.y >= 21.f && event.mouseButton.y <= 80.f) {
                        backupGame.set(score, words, wordCounter, lifesAmount);
                        gameState = GameState::EXIT_MENU;
                        return;
                    }
                }

            }

            background.move(-2.5f, 0.f);
            if (background.getPosition().x < -1000.f) {
                background.setPosition(0.f, 0.f);
            }

            window.clear(sf::Color::Black);

            window.draw(background);


            auto elapsed = clock.getElapsedTime();

            if (elapsed.asSeconds() > 3) {

                if (words.size() < 10) {

                    auto tmp = getText(24);

                    tmp.setString(chooseTextValue());

                    if(difficultyLevel == DifficultyLevel::HARD) {
                        auto rotationAngle = -30 + std::rand() % 60;
                        tmp.setRotation(rotationAngle);
                    }

                    words.push_back(tmp);
                }

                clock.restart();
            }


            for (auto &word: words) {

                word.move(2.f, 0.f);

                if (word.getPosition().x > 1250.f) {

                    word.setString(chooseTextValue());
                    word.setPosition(-100, infoPanel.getPosition().y - 20.f - std::rand() % 650);
                    lifesAmount--;

                }

                window.draw(word);

            }


            window.draw(infoPanel);

            window.draw(playerText);

            window.draw(scoreText);

            showElementsOnPanel(infoPanel);

            window.draw(wordLimit);

            window.draw(wordCountText);

            for (int i = 0; i < lifesAmount; i++) {
                life.setPosition(680.f + 40.f * i, window.getSize().y - infoPanel.getSize().y + 40);
                window.draw(life);
            }

            window.draw(menuIcon);

            window.display();

        }
    }


    auto resetSettings() -> void{
        lifesAmount = 5;
        score = std::string("000");
    }

    auto getRectanglePanel() -> sf::RectangleShape{
        auto res = sf::RectangleShape(sf::Vector2f(1200.f, 120.f));

        res.setPosition(0.f, window.getSize().y - res.getSize().y);

        res.setFillColor(sf::Color(5, 2, 20));

        return res;
    }

    auto showElementsOnPanel(sf::RectangleShape& infoPanel) -> void{

        auto textSCORE = getText(22);
        textSCORE.setString("SCORE : ");
        textSCORE.setPosition(950.f, infoPanel.getPosition().y + 35.f);

        auto inputLeftBorder = getText(30);
        inputLeftBorder.setString("[");
        inputLeftBorder.setPosition(5.f, infoPanel.getPosition().y + 20.f);

        auto inputRightBorder = getText(30);
        inputRightBorder.setString("]");
        inputRightBorder.setPosition(380.f, infoPanel.getPosition().y + 20.f);


        auto textWORDCOUNT = getText(22);
        textWORDCOUNT.setString("WORD COUNT");
        textWORDCOUNT.setPosition(450.f, infoPanel.getPosition().y + 10.f);

        auto textLIVES = getText(22);
        textLIVES.setString("LIVES : ");
        textLIVES.setPosition(740.f, infoPanel.getPosition().y + 10.f);


        window.draw(textSCORE);
        window.draw(inputRightBorder);
        window.draw(inputLeftBorder);
        window.draw(textWORDCOUNT);
        window.draw(textLIVES);

    }

};