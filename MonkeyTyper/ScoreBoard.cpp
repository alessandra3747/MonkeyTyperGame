#include "ScoreBoard.h"


ScoreBoard::ScoreBoard(){

    if (!textureScoreBoard.loadFromFile("../MyImages/BESTSCORES.png")) {
        fmt::println("Error - loading bestScores");
    }

    if (!scoreFontType.loadFromFile("../MyFonts/JaroFont.ttf"))
        fmt::println("Error - loading font in GameOver from file");


}


auto ScoreBoard::drawScoreBoard(sf::RenderWindow& window) -> void {

    auto scoreBoard = sf::Sprite(textureScoreBoard);
    scoreBoard.setPosition(47.4f, 503.8f);

    auto show = getText(26);
    show.setFillColor(sf::Color(248,46,255));
    show.setFont(scoreFontType);

    for(int i = 0; i < scores.size(); i++){
        show.setString(std::to_string(scores[i]));
        show.setPosition( 90.f, 565.f+(i * 40.f) );
        window.draw(show);
    }

    window.draw(scoreBoard);

}


auto ScoreBoard::addScore(int value) -> void {

    //push back ; pop back i sort

    if(scores.size() < 3) {
        scores.push_back(value);
        std::ranges::sort(scores, std::ranges::greater());
        return;
    }

    auto tmp = std::ranges::find_if(scores.begin(), scores.end(), [value](auto x){
        return value > x;
    });

    if( tmp != scores.end() ){
        scores.pop_back();
        this->addScore(value);
    }

}

