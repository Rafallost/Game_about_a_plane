#include "Parameters.h"

Parameters::Parameters()
{
	this->mouseHold = false;
	this->make();
	this->loadStats();
	this->loadRecord();
	this->initFont();
	this->initButons();
	this->initText();
}

Parameters::~Parameters()
{

}

void Parameters::make()
{
	if (!backgroundTexture.loadFromFile("assets/menu.png"))
		std::cout << "OJOJ\n";

	backgroundSprite.setTexture(backgroundTexture);
}


void Parameters::updateMousePos(sf::RenderWindow& mainWindow)
{
	//Updating mouse posiotion(vector2i) / aktualizacja pozycji myszki na wyswietlaczu(vector2i)
	this->mousePosWindow = sf::Mouse::getPosition(mainWindow);
	this->mousePosView = mainWindow.mapPixelToCoords(this->mousePosWindow);
}



void Parameters::initText()
{
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(36);
	this->uiText.setFillColor(sf::Color::White);
	this->uiText.setString("NONE");

	this->theHighestScore.setFont(this->font);
	this->theHighestScore.setCharacterSize(36);
	this->theHighestScore.setFillColor(sf::Color::Red);
	this->theHighestScore.setPosition(0.f, 800.f);
	this->theHighestScore.setString("NONE");

	this->textSpeed.setFont(this->font);
	this->textSpeed.setCharacterSize(36);
	this->textSpeed.setFillColor(sf::Color::White);
	this->textSpeed.setString("Increase speed");
	this->textSpeed.setPosition(50.f, 200.f);

	this->price[0].setFont(this->font);
	this->price[0].setCharacterSize(36);
	this->price[0].setFillColor(sf::Color::Yellow);
	this->price[0].setString("Price: 25 coins");
	this->price[0].setPosition(400.f, 200.f);


	this->textsize.setFont(this->font);
	this->textsize.setCharacterSize(36);
	this->textsize.setFillColor(sf::Color::White);
	this->textsize.setString("Decrease size");
	this->textsize.setPosition(50.f, 400.f);

	this->price[1].setFont(this->font);
	this->price[1].setCharacterSize(36);
	this->price[1].setFillColor(sf::Color::Yellow);
	this->price[1].setString("Price: 50 coins");
	this->price[1].setPosition(400.f, 400.f);

	this->textHp.setFont(this->font);
	this->textHp.setCharacterSize(36);
	this->textHp.setFillColor(sf::Color::White);
	this->textHp.setString("Increase hp");
	this->textHp.setPosition(50.f, 600.f);

	this->price[2].setFont(this->font);
	this->price[2].setCharacterSize(36);
	this->price[2].setFillColor(sf::Color::Yellow);
	this->price[2].setString("Price: 10 coins");
	this->price[2].setPosition(400.f, 600.f);

	this->notEnought.setFont(this->font);
	this->notEnought.setCharacterSize(72);
	this->notEnought.setFillColor(sf::Color::Red);
	this->notEnought.setString("Not Enought Coins!!!");
	this->notEnought.setPosition(800.f, 600.f);
}

void Parameters::initFont()
{
	if (!this->font.loadFromFile("assets/SourceSansPro-Regular.ttf"))
		std::cout << "ERROR::GAME::INITFONTS Fail do load font: assets/SourceSansPro-Regular.ttf!" << std::endl;
}

void Parameters::initButons()
{
	this->buttonSpeed.setFillColor(sf::Color(128, 128, 128));
	this->buttonSpeed.setOutlineColor(sf::Color::Black);
	this->buttonSpeed.setOutlineThickness(2.f);
	this->buttonSpeed.setPosition(0.f, 200.f);
	this->buttonSpeed.setSize(sf::Vector2f(300.f, 50.f));

	this->buttonSize.setFillColor(sf::Color(128, 128, 128));
	this->buttonSize.setOutlineColor(sf::Color::Black);
	this->buttonSize.setOutlineThickness(2.f);
	this->buttonSize.setPosition(0.f, 400.f);
	this->buttonSize.setSize(sf::Vector2f(300.f, 50.f));

	this->buttonHp.setFillColor(sf::Color(128, 128, 128));
	this->buttonHp.setOutlineColor(sf::Color::Black);
	this->buttonHp.setOutlineThickness(2.f);
	this->buttonHp.setPosition(0.f, 600.f);
	this->buttonHp.setSize(sf::Vector2f(300.f, 50.f));
}

void Parameters::loadStats()
{
	/*
	* loading from file plane statistics / ³adowanie z pliku statystyk samolotu
		1 line - amount of coins / ilosc monet
		2 line - speed lvl / prêdkoœæ
		3 line - size of plane / rozmiar samolotu
		4 line - max plane hp / max punktów ¿ycia samolotu
	*/

	std::ifstream status;

	status.open("status.txt");

	if (status.good())
	{
		std::string bufor;

		getline(status, bufor);
		this->coin = stoi(bufor);

		getline(status, bufor);
		this->speed = stoi(bufor);
		getline(status, bufor);
		this->size = std::stof(bufor);
		getline(status, bufor);
		this->hp = stoi(bufor);

		status.close();
	}
}

void Parameters::loadRecord()
{
	std::ifstream record;

	record.open("record.txt");

	if (record.good())
	{
		std::string bufor;

		getline(record, bufor);
		this->HighestScore = stoi(bufor);

		record.close();
	}
}


void Parameters::updateText()
{
	std::stringstream ss;

	ss << "Coins: " << this->coin << "\n"
		<< "Plane speed: " << this->speed << "\n"
		<< "Plane size: " << this->size << "\n"
		<< "Plane hp: " << this->hp << "\n";

	this->uiText.setString(ss.str());

	std::stringstream hight;

	hight << "Your the highest score is: " <<this->HighestScore<< "\n";

	this->theHighestScore.setString(hight.str());

}

void Parameters::updateTaransactions(sf::RenderWindow& mainWindow)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (!this->mouseHold)
		{
			this->mouseHold = true;

			if (this->buttonSpeed.getGlobalBounds().contains(mousePosView))
			{
				if (coin >= 25)
				{
					coin -= 25;
					this->speed += 1;

				}
				else
					mainWindow.draw(this->notEnought);
	
			}

			if (this->buttonSize.getGlobalBounds().contains(mousePosView))
			{
				if (coin >= 50 && this->size > 0.2f)
				{
					coin -= 50;
					this->size -= 0.1;
				}
				else
					mainWindow.draw(this->notEnought);
			}

			if (this->buttonHp.getGlobalBounds().contains(mousePosView))
			{
				if (coin >= 10)
				{
					coin -= 10;
					this->hp += 1;
				}
				else
					mainWindow.draw(this->notEnought);
			}
		}
	}
	else
	{
		this->mouseHold = false;
	}
}

void Parameters::updateParameters()
{
		std::ofstream status;

		status.open("status.txt");

		if (status.good())
		{
			std::string bufor;

			status << this->coin << "\n";
			status << this->speed << "\n";
			status << this->size << "\n";
			status << this->hp << "\n";


			status.close();
		}
}

void Parameters::update(sf::RenderWindow& mainWindow)
{
	mainWindow.draw(this->backgroundSprite);
	this->updateText();
	this->updateMousePos(mainWindow);
	this->updateTaransactions(mainWindow);
	this->updateParameters();
}


void Parameters::renderParameters(sf::RenderWindow& mainWindow)
{
	
	mainWindow.draw(this->uiText);
	mainWindow.draw(this->buttonSpeed);
	mainWindow.draw(this->buttonSize);
	mainWindow.draw(this->buttonHp);
	mainWindow.draw(this->textSpeed);
	mainWindow.draw(this->textsize);
	mainWindow.draw(this->textHp);
	mainWindow.draw(this->theHighestScore);
	
	for (int i = 0; i < 3; i++)
	{
		mainWindow.draw(this->price[i]);
	}

	
}
