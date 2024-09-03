#pragma once
#include <fmt/core.h>
#include <SFML/Graphics.hpp>
#include "GeneralSettings.h"
#include "ScoreBoard.h"

class BackUpGame {

protected:

    std::string prevScore;
    std::vector<sf::Text> prevWords;
    int prevWordCounter;
    int lifeAmount;

    bool isInitialized;

public:

    BackUpGame();



    auto set(const std::string prevScore, const std::vector<sf::Text> prevWords, int prevWordCounter, int lifeAmount) -> void;

    auto setInitialized(bool val) -> void;

    auto getIsInitialized() -> bool;


    auto getPrevScore() -> std::string;

    auto getPrevWords() -> std::vector<sf::Text>;

    auto getPrevWordCounter() -> int;

    auto getLifeAmount() -> int;

};