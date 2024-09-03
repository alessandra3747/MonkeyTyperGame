#include <fmt/core.h>
#include <SFML/Graphics.hpp>
#include "GeneralSettings.h"
#include "BackupGame.h"


    BackUpGame::BackUpGame() : prevScore(), prevWords(), prevWordCounter(), lifeAmount(), isInitialized(false){}


     auto BackUpGame::set(const std::string prevScore, const std::vector<sf::Text> prevWords, int prevWordCounter, int lifeAmount) -> void{
        this -> prevScore = prevScore;
        this -> prevWords = prevWords;
        this -> prevWordCounter = prevWordCounter;
        this -> lifeAmount = lifeAmount;
    }

    auto BackUpGame::setInitialized(bool val) -> void{
        this -> isInitialized = val;
    }


    auto BackUpGame::getIsInitialized() -> bool{
        return isInitialized;
    }


    auto BackUpGame::getPrevScore() -> std::string {
        return prevScore;
    }

    auto BackUpGame::getPrevWords() -> std::vector<sf::Text> {
        return prevWords;
    }

    auto BackUpGame::getPrevWordCounter() -> int {
        return prevWordCounter;
    }

    auto BackUpGame::getLifeAmount() -> int {
        return lifeAmount;
    }