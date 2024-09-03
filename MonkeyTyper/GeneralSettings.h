#pragma once
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "BackupGame.h"

enum class FontType{
    JOSEFINSANS = 1, OPENSANS = 2, ORBITRON = 3, OSWALD = 4, ROBOTOMONO = 5, TEKO = 6
};

enum class DifficultyLevel{
    EASY = 1, MEDIUM = 2, HARD = 3
};

enum class GameState{
    MENU = 0, PLAYING = 1, FONT = 2, DIFFICULTY = 3, EXIT = 4, GAMEOVER = 6, WIN = 7, EXIT_MENU = 8
};

auto changeFont(FontType fontVariance) -> void;

auto chooseTextValue() -> std::string;

auto changeDifficulty(DifficultyLevel diff) -> void;

auto setMaxWordAmount() -> int;

auto getText(int characterSize) -> sf::Text;

auto setWordsToChooseFrom() -> void;



inline auto wordsToChooseFrom = std::vector<std::string>();

inline auto difficultyLevel = DifficultyLevel::EASY;

inline auto font = sf::Font();

inline auto currentFontType = FontType::JOSEFINSANS;

inline auto gameState = GameState::MENU;

inline auto wordToChooseFromIndex = 0;

inline auto lifesAmount = 5;

inline auto maxWordAmount = setMaxWordAmount();

inline auto score = std::string("000");
inline auto highScore = 0;


inline auto backupGame = BackUpGame();

