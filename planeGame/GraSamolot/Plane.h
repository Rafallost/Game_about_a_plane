#pragma once

#include<iostream>
#include<vector>
#include<ctime>
#include<sstream>

#include "Bombs.h"
#include "Enemies.h"
#include "Coins.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Plane{

private:
	//Game logic / Zmienne logiczne
	int hp;
	int hpMax;
	int* hpPointer;
	int speedLvl;
	float scaleOfPlane;
	float planeSizeX;
	float planeSizeY;

	//objects / obiekty
	sf::RectangleShape plane;
	sf::Clock timeFromHit;
	sf::Clock timeFromCoin;

	//textures and sprites / Sprajty i texturty
	sf::Texture planeTexture;
	sf::Texture boomTexture;
	sf::Sprite planeSprite;

public:
	//friendship / klauzule przyjaüni
	friend class Game;
	friend class Enemies;
	friend class Coins;
	friend class Stats;
	friend class Bombs;

	//konstructor and destructor / konstruktor i destruktor
	Plane();
	virtual ~Plane();
	
	//initializing / inicjalizowanie
	void initPlane();
	void initVariables();

	//updating and rendering / aktualizacja i renderowanie 
	void updatePlane(sf::RenderWindow& mainWindow,Enemies& enemy, Bombs& bomb, Coins& coin, unsigned* score, int* coinsPointer);
	void renderPlane(sf::RenderTarget& target);
};


