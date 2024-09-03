#include "GeneralSettings.h"
#include "ScoreBoard.h"
#include "GameplayState.cpp"
#include "MenuState.cpp"
#include "StartScreen.cpp"
#include "FontState.cpp"
#include "DifficultyState.cpp"
#include "AfterGameState.cpp"
#include "ExitMenuState.cpp"

auto saveGame(ScoreBoard& scoreBoard) -> void;
auto readGame(ScoreBoard& scoreBoard) -> void;

int main() {

    auto window = sf::RenderWindow(
            sf::VideoMode(1200,800),
            "MonkeyTyper",
            sf::Style::Default,
            sf::ContextSettings(0,0,8)
    );


    auto scoreBoard = ScoreBoard();

    setWordsToChooseFrom();

    changeFont(FontType::JOSEFINSANS);

    readGame(scoreBoard);

    auto startScreen = StartScreen(window);
    startScreen.play();


    window.setFramerateLimit(60);

    while (window.isOpen()) {

        for (auto event = sf::Event(); window.pollEvent(event);) {

            if (event.type == sf::Event::Closed) {
                window.close();
            }

        }

        if (gameState == GameState::MENU) {
            auto menu = MenuState(window, scoreBoard);
            menu.play();
        }

        if (gameState == GameState::PLAYING) {
            auto gameplay = GameplayState(window, scoreBoard);
            gameplay.play();
        }

        if (gameState == GameState::GAMEOVER || gameState == GameState::WIN) {
            auto afterGameWindow = AfterGameState(window);
            afterGameWindow.play();
        }

        if (gameState == GameState::DIFFICULTY) {
            auto diffState = DifficultyState(window);
            diffState.play();
        }

        if (gameState == GameState::FONT) {
            auto fontState = FontState(window);
            fontState.play();
        }

        if (gameState == GameState::EXIT) {
            saveGame(scoreBoard);
            window.close();
        }

        if (gameState == GameState::EXIT_MENU) {
            auto exitMenu = ExitMenuState(window);
            exitMenu.play();
        }

    }

    return EXIT_SUCCESS;
}

auto saveGame(ScoreBoard& scoreBoard) -> void{

    //SCOREBOARD
    auto scoreboardStream = std::ofstream("../SavedGame/SavedScoreboard", std::ios::trunc);

    for (auto sc: scoreBoard.getScores()) {
        scoreboardStream << sc;
        scoreboardStream << "\n";
    }

    scoreboardStream.close();


    //SETTINGS
    auto settingsStream = std::ofstream("../SavedGame/Settings", std::ios::trunc);

    settingsStream << static_cast<int>(difficultyLevel) << "\n";
    settingsStream << static_cast<int>(currentFontType) << "\n";
    settingsStream << wordToChooseFromIndex << "\n";


    if(backupGame.getIsInitialized()) {
        settingsStream << "true" << "\n";
        settingsStream << backupGame.getPrevScore() << "\n";
        settingsStream << backupGame.getLifeAmount() << "\n";
        settingsStream << backupGame.getPrevWordCounter() << "\n";
    } else
        settingsStream << "false" << "\n";

    settingsStream.close();



    //WORDS
    if (backupGame.getIsInitialized()) {

        auto wordsStream = std::ofstream("../SavedGame/WordsVector", std::ios::trunc);

        for (auto& w: backupGame.getPrevWords()) {
            wordsStream << w.getPosition().x;
            wordsStream << "\n";
            wordsStream << w.getPosition().y;
            wordsStream << "\n";
            wordsStream << w.getString().toAnsiString();
            wordsStream << "\n";
        }

        wordsStream.close();
    }

}

auto readGame(ScoreBoard& scoreBoard) -> void {


    //SCOREBOARD
    auto scoreboardStream = std::fstream("../SavedGame/SavedScoreboard");

    auto sc = int();
    while(scoreboardStream >> sc){
        scoreBoard.addScore(sc);
    }

    scoreboardStream.close();


    //SETTINGS AND GAME
    auto settingsStream = std::fstream("../SavedGame/Settings");

    auto setting = int();

    settingsStream >> setting;
    difficultyLevel = static_cast<DifficultyLevel>(setting);

    settingsStream >> setting;
    currentFontType = static_cast<FontType>(setting);

    settingsStream >> setting;
    wordToChooseFromIndex = setting;



    auto uploadGame = std::string();
    settingsStream >> uploadGame;


    if(uploadGame == "true") {

        auto loadedScore = std::string();
        settingsStream >> loadedScore;

        auto loadedLifeAmount = int();
        settingsStream >> loadedLifeAmount;

        auto loadedWordCounter = int();
        settingsStream >> loadedWordCounter;

        settingsStream.close();


        auto loadedWords = std::vector<sf::Text>();

        auto wordsStream = std::fstream("../SavedGame/WordsVector");

        auto wordToPushBack = getText(24);

        auto xPosition = int();
        auto yPosition = int();
        auto wordString = std::string();

        while(!wordsStream.eof()){
            wordsStream >> xPosition;
            wordsStream >> yPosition;
            wordsStream >> wordString;

            wordToPushBack.setPosition(xPosition, yPosition);
            wordToPushBack.setString(wordString);

            loadedWords.push_back(wordToPushBack);
        }

        wordsStream.close();

        backupGame.set(loadedScore, loadedWords, loadedWordCounter, loadedLifeAmount);
        backupGame.setInitialized(true);

    } else {
        settingsStream.close();
    }


}