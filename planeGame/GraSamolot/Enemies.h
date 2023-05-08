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

class Enemies{

private:
	//Game logic
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	float enemiesSpeed;
	int enemyMax;

	//objects
	sf::Texture enemyTextureBird;
	sf::Texture enemyTextureRock;
	sf::Texture enemyTextureBigplane;

	sf::Sprite enemySpriteBird;
	sf::Sprite enemySpriteRock;
	sf::Sprite enemySpriteBigplane;
	std::vector<sf::Sprite> enemiesSprites;
	

public:
	//frindship
	friend class Game;
	friend class Plane;

	//constructor and destructor / konstruktor i destruktor
	Enemies();
	virtual ~Enemies();
	
	//initialization
	void initEnemies();
	void initVariables();
	
	//spawning
	void spawnEnemy(sf::RenderTarget* window);

	//upadate and render
	void updateEnemies(sf::RenderTarget* window);
	void rederEnemies(sf::RenderTarget& target);


};
