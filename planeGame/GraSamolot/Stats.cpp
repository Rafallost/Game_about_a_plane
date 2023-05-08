#include "Stats.h"
#include "Plane.h"

Stats::Stats()
{
    this->initText();
    this->initFont();
}

Stats::~Stats()
{

}

void Stats::initText()
{
    this->uiText.setFont(this->font);
    this->uiText.setCharacterSize(36);
    this->uiText.setFillColor(sf::Color::White);
    this->uiText.setString("NONE");
}

void Stats::initFont()
{
    if (!this->font.loadFromFile("assets/SourceSansPro-Regular.ttf"))
        std::cout << "ERROR::GAME::INITFONTS Fail do load font: assets/SourceSansPro-Regular.ttf!" << std::endl;
}

void Stats::updateText(Plane& plane, unsigned* score, int* coinsPointer)
{
    std::stringstream ss;

    ss << "score: " << *score << "\n" << "Health: " << plane.hp << "\n" << "Coins: " << *coinsPointer;

    this->uiText.setString(ss.str());
}

void Stats::renderText(sf::RenderTarget& target)
{
    target.draw(this->uiText);
}
