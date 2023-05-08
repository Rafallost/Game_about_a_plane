#include "Menu.h"
#include "Plane.h"

Menu::Menu(float width, float height)
{
	this->loadStats();
	this->make();
}

Menu::~Menu()
{

}

void Menu::loadStats()
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

void Menu::make()
{
	if (!this->font.loadFromFile("assets/SourceSansPro-Regular.ttf"))
		std::cout << "ERROR::GAME::INITFONTS Fail do load font!" << std::endl;

	//New Game
	this->menuTextures[0].setFont(font);
	this->menuTextures[0].setFillColor(sf::Color::White);
	this->menuTextures[0].setString("Restart Game Progress");
	this->menuTextures[0].setCharacterSize(70);
	this->menuTextures[0].setPosition(400, 200);
	
	//Play
	this->menuTextures[1].setFont(font);
	this->menuTextures[1].setFillColor(sf::Color::White);
	this->menuTextures[1].setString("Load Game");
	this->menuTextures[1].setCharacterSize(70);
	this->menuTextures[1].setPosition(400, 300);

	//Options
	this->menuTextures[2].setFont(font);
	this->menuTextures[2].setFillColor(sf::Color::White);
	this->menuTextures[2].setString("Options");
	this->menuTextures[2].setCharacterSize(70);
	this->menuTextures[2].setPosition(400, 400);

	//Parameters
	this->menuTextures[3].setFont(font);
	this->menuTextures[3].setFillColor(sf::Color::White);
	this->menuTextures[3].setString("Parameters");
	this->menuTextures[3].setCharacterSize(70);
	this->menuTextures[3].setPosition(400, 500);

	//Exit
	this->menuTextures[4].setFont(font);
	this->menuTextures[4].setFillColor(sf::Color::White);
	this->menuTextures[4].setString("Exit");
	this->menuTextures[4].setCharacterSize(70);
	this->menuTextures[4].setPosition(400, 600);

	//Reset
	this->restarted.setFont(this->font);
	this->restarted.setFillColor(sf::Color::Black);
	this->restarted.setString("GAME PROGRESS WAS RESTARTED");
	this->restarted.setCharacterSize(70);
	this->restarted.setPosition(850,500);

	this->menuSelected = -1;

	if (!this->backgroundTexture.loadFromFile("assets/menu1.jpg"))
		std::cout << "ERROR: XD\n";
	this->backgroundSprite.setTexture(backgroundTexture);
}

void Menu::resetProgress()
{

	std::ofstream status;

	status.open("status.txt");

	if (status.good())
	{
		std::string bufor;

		status << 0 << "\n";
		status << 3 << "\n";
		status << 0.6f << "\n";
		status << 3 << "\n";


		status.close();
	}
}

void Menu::moveUp()
{
	if (menuSelected - 1 >= 0)
	{
		menuTextures[menuSelected].setFillColor(sf::Color::White);
		menuSelected--;
		
		if (menuSelected == -1)
		{
			menuSelected = 2;
		}

		menuTextures[menuSelected].setFillColor(sf::Color::Black);
	}
}

void Menu::moveDown()
{
	if (menuSelected + 1 <= menuMaxOptions)
	{
		menuTextures[menuSelected].setFillColor(sf::Color::White);
		menuSelected++;

		if (menuSelected == menuMaxOptions)
		{
			menuSelected = 0;
		}

		menuTextures[menuSelected].setFillColor(sf::Color::Black);
	}
}

void Menu::renderMenuRestarted(sf::RenderWindow& win)
{
	win.draw(this->restarted);

}

void Menu::renderMenu(sf::RenderWindow& win)
{
	win.draw(this->backgroundSprite);

	for (int i = 0; i < menuMaxOptions; ++i)
	{
		win.draw(this->menuTextures[i]);
	}
}
