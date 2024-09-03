#include "GeneralSettings.h"
#include <fstream>

auto changeFont(FontType fontVariance) -> void {

//fonts from Google Fonts

    switch(fontVariance){

        case FontType::JOSEFINSANS:
            if (!font.loadFromFile("../MyFonts/JosefinSans.ttf"))
                fmt::println("Error - loading font from file");
            currentFontType = FontType::JOSEFINSANS;
            break;

        case FontType::OPENSANS:
            if (!font.loadFromFile("../MyFonts/OpenSans.ttf"))
                fmt::println("Error - loading font from file");
            currentFontType = FontType::OPENSANS;
            break;

        case FontType::ORBITRON:
            if (!font.loadFromFile("../MyFonts/Orbitron.ttf"))
                fmt::println("Error - loading font from file");
            currentFontType = FontType::ORBITRON;
            break;

        case FontType::OSWALD:
            if (!font.loadFromFile("../MyFonts/Oswald.ttf"))
                fmt::println("Error - loading font from file");
            currentFontType = FontType::OSWALD;
            break;

        case FontType::ROBOTOMONO:
            if (!font.loadFromFile("../MyFonts/RobotoMono.ttf"))
                fmt::println("Error - loading font from file");
            currentFontType = FontType::ROBOTOMONO;
            break;

        default:
            if (!font.loadFromFile("../MyFonts/JosefinSans.ttf"))
                fmt::println("Error - loading font from file");
            break;
    }

}


auto changeDifficulty(DifficultyLevel diff) -> void {

    difficultyLevel = diff;

    setMaxWordAmount();

    setWordsToChooseFrom();

}


auto setWordsToChooseFrom() -> void {

    auto path = std::string();

    switch(difficultyLevel) {
        case(DifficultyLevel::EASY):
            path = "../MyWords/Easy";
            break;

        case (DifficultyLevel::MEDIUM):
            path = "../MyWords/Medium";
            break;

        case(DifficultyLevel::HARD):
            path = "../MyWords/Hard";
            break;
    }

    auto file = std::fstream(path);

    wordsToChooseFrom.clear();

    auto word = std::string();

    while (file >> word)
        wordsToChooseFrom.push_back(word);

}

auto chooseTextValue() -> std::string {
    if(wordToChooseFromIndex == maxWordAmount-1)
        wordToChooseFromIndex = 0;

    return wordsToChooseFrom[wordToChooseFromIndex++];
}


auto getText(int characterSize) -> sf::Text {

    auto text = sf::Text();

    text.setFont(font);

    text.setCharacterSize(characterSize);

    text.setFillColor(sf::Color::Green);

    text.setStyle(sf::Text::Bold);

    text.setPosition(-50.f, 50.f + std::rand() % 550);

    return text;

}


auto setMaxWordAmount() -> int {

    switch (difficultyLevel) {

        case DifficultyLevel::MEDIUM:
            maxWordAmount = 250;
            break;

        case DifficultyLevel::HARD:
            maxWordAmount = 260;
            break;

        default:
            maxWordAmount = 275;
            break;
    }

    return maxWordAmount;

}

