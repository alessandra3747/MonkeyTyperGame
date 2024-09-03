#pragma once
#include "GeneralSettings.h"

class ScoreBoard{
protected:
    std::vector<int> scores;
    sf::Texture textureScoreBoard;
    sf::Font scoreFontType;

public:
    ScoreBoard();

    auto getScores() -> std::vector<int>{
        return scores;
    }

    auto drawScoreBoard(sf::RenderWindow& window) -> void;

    auto addScore(int value) -> void;
};

