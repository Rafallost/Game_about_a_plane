#pragma once

#include<iostream>
#include<vector>
#include<ctime>
#include<sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Coins {

private:

	//Game logic
	float coinsSpeed;
	float coinSpawnTimer;
	float coinSpawnMax;
	int maxCoins;

	//objects
	//objects
	sf::Texture coinTexture;
	sf::Sprite coinSprite;
	std::vector<sf::Sprite> coinsSprites;

public:
	//frindship
	friend class Game;
	friend class Plane;

	//konstrucotor and destruktor
	Coins();
	virtual ~Coins();

	//initcializaction
	void initCoins();
	void initVariables();

	//spawning
	void spawnCoins(sf::RenderTarget* window);

	//update and render
	void updateCoins(sf::RenderTarget* window);
	void renderCoins(sf::RenderTarget& target);
};