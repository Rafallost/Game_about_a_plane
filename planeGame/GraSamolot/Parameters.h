#pragma once

#include<iostream>
#include<vector>
#include<ctime>
#include<sstream>
#include<fstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Parameters {

private:

	//background / t³o
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	
	//buttons / przyciski
	sf::RectangleShape buttonSpeed;
	sf::RectangleShape buttonSize;
	sf::RectangleShape buttonHp;
	sf::Text textSpeed;
	sf::Text textsize;
	sf::Text textHp;
	sf::Text price[3];
	sf::Text theHighestScore;
	sf::Text notEnought;
	bool mouseHold;

	//reading from file / czytanie z pliku
	int HighestScore;
	int coin;
	int speed;
	float size;
	int hp;

	//text / teks
	sf::Font font;
	sf::Text uiText;

	//Mouse position / pozycja myszki
	sf::Vector2i mousePosWindow; //On the sceen / Na wyœwietlaczu
	sf::Vector2f mousePosView;   //On the Window / Na wyœwietlanym oknie

public:
		//constructor and destructor
		Parameters();
		~Parameters();

		//initializing / inicjalizacje
		void make();
		void loadStats();
		void loadRecord();
		void initFont();
		void initText();
		void initButons();

		//update / aktualizacja
		void update(sf::RenderWindow& mainWindow);
		void updateMousePos(sf::RenderWindow& mainWindow);
		void updateTaransactions(sf::RenderWindow& mainWindow);
		void updateParameters();
		void updateText();

		void renderParameters(sf::RenderWindow& mainWindow);
};