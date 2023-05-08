#include <iostream>

#include "Game.h"
#include "Options.h"
#include "Parameters.h"

#include<iostream>
#include<vector>
#include<ctime>
#include<sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


int main()
{
    //random numbers / liczby pseudolosowe
    srand(static_cast<unsigned>(time(NULL)));

    //Main window / okno gry
    sf::RenderWindow mainWindow(sf::VideoMode(1200, 800), "Sky explorer",sf::Style::Fullscreen);
   
    //Frame limit / ograniczenie klatek na sekunde
    mainWindow.setFramerateLimit(60);
    
    //menu window / okno menu
    Menu menu(mainWindow.getSize().x, mainWindow.getSize().y);

    //music / muzyka
    sf::Music music;

    if (!music.openFromFile("assets/gameMusic.ogg"))
        std::cout << "WOOPS\n";

    music.play();
    music.setVolume(5);
    music.setLoop(true);

    //Game loop / Gra
    while (mainWindow.isOpen())
    {
        //updating / aktualizacja po³o¿enia
        sf::Event event;
        
        while(mainWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                mainWindow.close();
            }

            if (event.type == sf::Event::KeyReleased)
            {
                
                if (event.key.code == sf::Keyboard::Up)
                {
                    menu.moveUp();
                    break;

                }

                if (event.key.code == sf::Keyboard::Down)
                {
                    menu.moveDown();
                    break;
                }

                if (event.key.code == sf::Keyboard::Enter)
                {
                    bool backToMain = false;

                    int x = menu.menuPressed();
                    
                    //option play / opcja play
                    if (x == 1)
                    {
                        // Game Over Appearance / Wygl¹d napisu Game Over
                        sf::Texture gameOver;
                        if (!gameOver.loadFromFile("assets/GameOver.png"))
                            std::cout << "ojoj\n";
                        sf::Sprite gameOverSprite;

                        gameOverSprite.setTexture(gameOver);
                        gameOverSprite.setPosition(500.f, 300.f);

                        Game game;

                        while (!game.getEndGame() && !backToMain)
                        {
                            sf::Event evInside;
                            while (mainWindow.pollEvent(evInside))
                            {
                                if (evInside.type == sf::Event::Closed)
                                {
                                    mainWindow.close();
                                }
                                if (evInside.type == sf::Event::KeyPressed)
                                {
                                    if (evInside.key.code == sf::Keyboard::Escape)
                                    {
                                        backToMain = true;
                                        break;
                                    }
                                }
                            }
                            game.update(mainWindow);

                            if (game.getEndGame())
                            {
                                mainWindow.draw(gameOverSprite);
                                mainWindow.display();

                                sf::Event end;
                                int nowEnd = 1;
                                while(nowEnd)
                                    while (mainWindow.pollEvent(end))
                                        if (end.type == sf::Event::KeyReleased)
                                            if (end.key.code == sf::Keyboard::Escape)
                                                nowEnd = 0;
                            }

                            game.render(mainWindow);
                        }
                    }

                    //option options / opcja opcje
                    else if (x == 2)
                    {
                        Options opt;

                        while (!backToMain)
                        {
                            sf::Event evInside;
                            while (mainWindow.pollEvent(evInside))
                            {
                                if (evInside.type == sf::Event::Closed)
                                {
                                    mainWindow.close();
                                }
                                if (evInside.type == sf::Event::KeyPressed)
                                {
                                    if (evInside.key.code == sf::Keyboard::Escape)
                                    {
                                        backToMain = true;
                                        break;
                                    }
                                }
                            }
                            mainWindow.clear();
                            opt.update(mainWindow,music);
                            opt.renderOptions(mainWindow);
                            mainWindow.display();
                        }
                    }
                    //option parameters / opcja parametry
                    else if (x == 3)
                    {
                        Parameters para;
                        while (!backToMain)
                        {
                            sf::Event evInside;
                            while (mainWindow.pollEvent(evInside))
                            {
                                if (evInside.type == sf::Event::Closed)
                                {
                                    mainWindow.close();
                                }
                                if (evInside.type == sf::Event::KeyPressed)
                                {
                                    if (evInside.key.code == sf::Keyboard::Escape)
                                    {
                                        backToMain = true;
                                        break;
                                    }
                                }
                            }
                            mainWindow.clear();
                            para.update(mainWindow);
                            para.renderParameters(mainWindow);
                            mainWindow.display();
                        }
                    }
                    //option Exit / opcja Exit
                    else if (x == 4)
                        mainWindow.close();
                    
                    // New game / nowa gra
                    else if (x == 0)
                    {
                        menu.resetProgress();

                        while (!backToMain)
                        {
                            sf::Event evInside;
                            while (mainWindow.pollEvent(evInside))
                            {
                                if (evInside.type == sf::Event::Closed)
                                {
                                    mainWindow.close();
                                }
                                if (evInside.type == sf::Event::KeyPressed)
                                {
                                    backToMain = true;
                                    break;

                                }
                            }
                            mainWindow.clear();
                            menu.renderMenu(mainWindow);
                            menu.renderMenuRestarted(mainWindow);
                            mainWindow.display();
                        }
                    }
                    break;
                }
            }
        }
        //delete old frame / usuwanie starej klatki
        mainWindow.clear();

        //render / za³adowanie nowej klatki
        menu.renderMenu(mainWindow);
        
        //display / wyœwietlenie nowej klatki
        mainWindow.display();
    }

    music.stop();
    return 0;
}
