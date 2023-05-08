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

#define maxButtons 2

class Options {

private:
	//background / t³o
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

	//buttons
	bool mouseHold;
	int musicVolume;
	sf::Font font;
	sf::Text musicVolumeText;
	sf::Text buttonsText[maxButtons];
	sf::RectangleShape buttonsView[maxButtons];

	//Mouse position / pozycja myszki
	sf::Vector2i mousePosWindow; //On the sceen / Na wyœwietlaczu
	sf::Vector2f mousePosView;   //On the Window / Na wyœwietlanym oknie

public:
	//constructor and destructor
	Options();
	~Options();

	//inits
	void initBackground();
	void initText();
	void initShapes();

	//update
	void updateMousePos(sf::RenderWindow& mainWindow);
	void updateText();
	void update(sf::RenderWindow& mainWindow,sf::Music& music);

	//render
	void renderOptions(sf::RenderWindow& mainWindow);
};