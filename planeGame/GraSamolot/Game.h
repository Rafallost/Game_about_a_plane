#pragma once

#include "Enemies.h"
#include "Bombs.h"
#include "Coins.h"
#include "Plane.h"
#include "Stats.h"
#include "Menu.h"

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

class Game
{
private:
	//Mouse position / pozycja myszki
	sf::Vector2i mousePosWindow; //On the sceen / Na wy�wietlaczu
	sf::Vector2f mousePosView;   //On the Window / Na wy�wietlanym oknie

	//Game logic / zamnienne logiczne
	bool endGame;
	int coins;
	int* coinsPointer;
	
	// score logic / logika dzia�ania punkt�w
	unsigned score;
	unsigned* scorePointer;
	sf::Clock timeIsScore;
	sf::Clock timeIsDifficulty;
	bool was1, was2;
	int howMuchWas;
	int theHighestScore;

	//Game objects / Obiekty w grze
	Enemies enemy;
	Bombs bomb;
	Coins coin;
	Plane plane;
	Stats stats;

	//Textures and sprites / tekstury i sprite'y
	sf::Texture backGroundTexture;
	sf::Sprite backGroundSprite;

	//Changing difficulty level  / zmienianie poziomu trudno�ci
	void changingDifficulty();

	//inits / inicjalizacje
	void initVariables();
	void initBackGroundTexture();
	
	//loading and initialiazing stats from file / za�adowanie i inicjalizacja statystyk z pliku
	void loadStats();

	//saving progress / zapis prograsu
	void saveStats();
	void saveTheHighestScore();

	//Adding score / dodawanie punkt�w
	void addingscore();

public:
	//Friendship / klauzule przyja�ni
	friend class Enemies;
	friend class Coins;
	friend class Plane;
	friend class Bombs;
	friend class Stats;
	friend int main();

	//constructor and destructor / konstruktor i destruktor
	Game();
	virtual ~Game();

	// Accessories / Akcesoria
	const bool getEndGame() const;

	//update / aktualizacja po�o�enia
	void updateMousePos(sf::RenderWindow& mainWindow);
	void update(sf::RenderWindow& mainWindow);
	
	//render / renderowanie po�o�enia
	void render(sf::RenderWindow& mainWindow);


};

