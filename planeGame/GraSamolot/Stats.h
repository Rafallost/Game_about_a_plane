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

class Stats {
private:

	//Objects
	sf::Font font;
	sf::Text uiText;


public:
	//frindship
	friend class Game;
	friend class Plane;

	Stats();
	virtual ~Stats();

	//inicializing
	void initText();
	void initFont();

	//updating
	void updateText(Plane& plane, unsigned* score,int* coinsPointer);

	//render
	void renderText(sf::RenderTarget& target);
};