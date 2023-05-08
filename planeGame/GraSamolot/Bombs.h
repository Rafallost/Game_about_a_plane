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

class Bombs {

private:
	//Game logic
	float bombsSpeed;
	float bombSpawnTimer;
	float bombSpawnTimerMax;
	int bombMax;
	bool mouseHeld;

	//objects
	sf::Texture bombTexture;
	sf::Sprite bombSprite;
	std::vector<sf::Sprite> bombsSprites;
public:
	//frindship
	friend class Game;
	friend class Plane;

	//konstruktor and destruktor
	Bombs();
	virtual ~Bombs();

	//inicialization
	void initBomb();
	void initVariables();

	//spawning
	void spawnBomb(sf::RenderTarget* window);

	//upadate and render
	void updateBomb(sf::RenderTarget* window,sf::Vector2f mousePosView, unsigned* score, int* hp);
	void rederBomb(sf::RenderTarget& target);


};