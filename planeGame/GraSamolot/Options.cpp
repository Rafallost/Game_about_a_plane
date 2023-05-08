#include "Options.h"

Options::Options()
{
	this->mouseHold = false;
	this->initBackground();
	this->initShapes();
	this->initText();
}

Options::~Options()
{

}

void Options::initBackground()
{
	if (!this->backgroundTexture.loadFromFile("assets/menu.png"))
		std::cout << "ERROR: assets/menu.png\n";
	this->backgroundSprite.setTexture(backgroundTexture);
}

void Options::initShapes()
{
	this->buttonsView[0].setFillColor(sf::Color(128, 128, 128));
	this->buttonsView[0].setOutlineColor(sf::Color::Black);
	this->buttonsView[0].setOutlineThickness(2.f);
	this->buttonsView[0].setPosition(0.f, 150.f);
	this->buttonsView[0].setSize(sf::Vector2f(400.f, 50.f));

	this->buttonsView[1].setFillColor(sf::Color(128, 128, 128));
	this->buttonsView[1].setOutlineColor(sf::Color::Black);
	this->buttonsView[1].setOutlineThickness(2.f);
	this->buttonsView[1].setPosition(0.f, 350.f);
	this->buttonsView[1].setSize(sf::Vector2f(400.f, 50.f));
}

void Options::initText()
{
	if (!this->font.loadFromFile("assets/SourceSansPro-Regular.ttf"))
		std::cout << "ERROR::GAME::initText() Fail do load font: assets/SourceSansPro-Regular.ttf!" << std::endl;

	this->buttonsText[0].setFont(this->font);
	this->buttonsText[0].setCharacterSize(36);
	this->buttonsText[0].setFillColor(sf::Color::White);
	this->buttonsText[0].setString("+ 5 music volume");
	this->buttonsText[0].setPosition(50.f, 150.f);

	this->buttonsText[1].setFont(this->font);
	this->buttonsText[1].setCharacterSize(36);
	this->buttonsText[1].setFillColor(sf::Color::White);
	this->buttonsText[1].setString("- 5 music volume");
	this->buttonsText[1].setPosition(50.f, 350.f);

	this->musicVolumeText.setFont(this->font);
	this->musicVolumeText.setCharacterSize(36);
	this->musicVolumeText.setFillColor(sf::Color::Black);
	this->musicVolumeText.setString("None");
	this->musicVolumeText.setPosition(50.f, 50.f);

}

void Options::updateText()
{

	std::stringstream ss;

	ss << "Currend Volume level: " << this->musicVolume << "\n";

	this->musicVolumeText.setString(ss.str());
}

void Options::updateMousePos(sf::RenderWindow& mainWindow)
{
	//Updating mouse posiotion(vector2i) / aktualizacja pozycji myszki na wyswietlaczu(vector2i)
	this->mousePosWindow = sf::Mouse::getPosition(mainWindow);
	this->mousePosView = mainWindow.mapPixelToCoords(this->mousePosWindow);
}

void Options::update(sf::RenderWindow& mainWindow, sf::Music& music)
{
	
	this->updateMousePos(mainWindow);

	this->musicVolume = music.getVolume();

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (!this->mouseHold)
		{
			this->mouseHold = true;

			if (this->buttonsView[0].getGlobalBounds().contains(this->mousePosView))
			{
				this->musicVolume += 5;
			}

			if (this->buttonsView[1].getGlobalBounds().contains(this->mousePosView))
			{
				if (this->musicVolume >= 5)
					this->musicVolume -= 5;
				else
					this->musicVolume = 0;
			}
			music.setVolume(this->musicVolume);
		}
	}
	else
	{
		this->mouseHold = false;
	}

	this->updateText();
}

void Options::renderOptions(sf::RenderWindow& mainWindow)
{
	mainWindow.draw(this->backgroundSprite);
	mainWindow.draw(this->musicVolumeText);
	for (int i = 0; i < maxButtons; i++)
	{
		mainWindow.draw(this->buttonsView[i]);
		mainWindow.draw(this->buttonsText[i]);
	}
}
