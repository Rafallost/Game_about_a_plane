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

#define menuMaxOptions  5

class Menu {
private:

	//reading from file / czytanie z pliku
	int coin;
	int speed;
	float size;
	int hp;

	//menu logic / logika menu
	int menuSelected;
	sf::Font font;
	sf::Text menuTextures[menuMaxOptions];
	sf::Text restarted;
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

public:
	//konstructor and destructor
	Menu(float width , float height );
	~Menu();

	//functions
	void moveUp();
	void moveDown();

	void make();
	void loadStats();
	void resetProgress();

	int menuPressed()
	{
		return menuSelected;
	}

	//render
	void renderMenu(sf::RenderWindow& win);
	void renderMenuRestarted(sf::RenderWindow& win);
};