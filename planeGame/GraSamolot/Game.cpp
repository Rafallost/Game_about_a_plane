#include "Game.h"
#include "Enemies.h"
#include "Bombs.h"
#include "Coins.h"
#include "Plane.h"
#include "Menu.h"

//constructor and destructor / kontruktor i destruktor
Game::Game()
{
    //game inits / inicjalizacje metod z clasy
	this->initVariables();
    this->initBackGroundTexture();
    
    //loading progress / za³adowanie postêpu
    this->loadStats();

    //objects inits / inicjalizacje metod z obiektów
    this->enemy.initEnemies();
    this->enemy.initVariables();
    this->bomb.initBomb();
    this->bomb.initVariables();
    this->coin.initCoins();
    this->coin.initVariables();
    this->plane.initPlane();
    this->plane.initVariables();
    this->stats.initFont();
    this->stats.initText();
}

Game::~Game()
{

}

//Accessories / Akcesoria

const bool Game::getEndGame() const
{
    return this->endGame;
}

void Game::addingscore()
{
    if (timeIsScore.getElapsedTime().asMilliseconds() > 10.f)
    {
        this->score += 1;
        timeIsScore.restart();
    }
}

void Game::changingDifficulty()
{
    if ((timeIsDifficulty.getElapsedTime().asSeconds() > 5.f) && !was1)
    {
        if(enemy.enemyMax<15.f)
            enemy.enemyMax += 1.f;

        enemy.enemiesSpeed += 0.5f;
        coin.coinsSpeed += 0.5f;
        bomb.bombsSpeed += 0.5f;
        this->was1 = true;
        this->howMuchWas++;
    }
    if ((timeIsDifficulty.getElapsedTime().asSeconds() > 10.f) && !was2)
    {
        if (enemy.enemyMax < 15.f)
            enemy.enemyMax += 1.f;

        enemy.enemiesSpeed += 0.25f;
        coin.coinsSpeed += 0.25f;
        bomb.bombsSpeed += 0.25f;
        this->was2 = true;
        this->howMuchWas++;
        std::cout << "Speed: " << enemy.enemiesSpeed << "\n";
        std::cout << "how much: " << howMuchWas << "\n";
    }

    if (timeIsDifficulty.getElapsedTime().asSeconds() > 15.f && (this->howMuchWas == 2))
    {
        bomb.bombMax += 1.f;
        this->was1 = false;
        this->was2 = false; 
        this->howMuchWas = 4;
        timeIsDifficulty.restart();
    }

    if (timeIsDifficulty.getElapsedTime().asSeconds() > 15.f && (this->howMuchWas == 12))
    {
        if(bomb.bombMax < 5.f)
            bomb.bombMax += 1.f;

        this->was1 = false;
        this->was2 = false;
        this->howMuchWas = 4;
        timeIsDifficulty.restart();
        std::cout << "Speed: " << enemy.enemiesSpeed << "\n";
    } 

    if (timeIsDifficulty.getElapsedTime().asSeconds() > 15.f)
    {
        this->was1 = false;
        this->was2 = false;
        timeIsDifficulty.restart();
    }
}

//Inits / Inicjalizacje

void Game::initVariables()
{
    //Game logic
    this->score = 0;
    this->endGame = false;
    this->was1 = false;
    this->was2 = false;
    this->howMuchWas = 0;
    this->scorePointer = &score;
    this->coinsPointer = &coins;
}

void Game::initBackGroundTexture()
{
    this->backGroundTexture.loadFromFile("assets/sky_true.png");

    this->backGroundTexture.setRepeated(true);
    this->backGroundSprite.setTexture(this->backGroundTexture);
}

//files operations / operacje na plikach
void Game::loadStats()
{
    /*
    * loading from file plane statistics / ³adowanie z pliku statystyk samolotu
        1 line - amount of coins / ilosc monet
        2 line - speed / prêdkoœæ
        3 line - size of plane / rozmiar samolotu
        4 line - max plane hp / max punktów ¿ycia samolotu
    */

    std::ifstream status;

    status.open("status.txt");

    if (status.good())
    {
        std::string bufor;

        getline(status, bufor);
        this->coins = stoi(bufor);
        getline(status, bufor);
        this->plane.speedLvl = stoi(bufor);
        getline(status, bufor);
        this->plane.scaleOfPlane = std::stof(bufor);
        getline(status, bufor);
        this->plane.hp= stoi(bufor);

        this->plane.hpMax = this->plane.hp;
       
        status.close();
    }
}

void Game::saveStats()
{
    //Save plane statistics to file / zapis do pliku statystyk samolotu
    std::ofstream status;

    status.open("status.txt");

    if (status.good())
    {
        
        status << this->coins<<"\n";
        status << this->plane.speedLvl << "\n";
        status << this->plane.scaleOfPlane<< "\n";
        status << this->plane.hpMax << "\n";

        status.close();
    }
}

void Game::saveTheHighestScore()
{
    std::ifstream record;
    
    record.open("record.txt");

    if (record.good())
    {
        std::string bufor;

        getline(record, bufor);
        this->theHighestScore = stoi(bufor);

        if (this->score > this->theHighestScore)
        {
            record.close();

            std::ofstream record;

            record.open("record.txt");

            if(record.good())
                record << this->score << "\n";
        }
        record.close();
    }
}


//update / aktualizacja

void Game::updateMousePos(sf::RenderWindow& mainWindow)
{
    //Updating mouse posiotion(vector2i) / aktualizacja pozycji myszki na wyswietlaczu(vector2i)
    this->mousePosWindow = sf::Mouse::getPosition(mainWindow);
    this->mousePosView = mainWindow.mapPixelToCoords(this->mousePosWindow);
}

void Game::update(sf::RenderWindow& mainWindow)
{
    //updating events
    if (!this->endGame)
    {
        this->updateMousePos(mainWindow);
        this->addingscore();
        this->changingDifficulty();
        this->coin.updateCoins(&mainWindow);
        this->enemy.updateEnemies(&mainWindow);
        this->bomb.updateBomb(&mainWindow,this->mousePosView,this->scorePointer,this->plane.hpPointer);
        this->plane.updatePlane(mainWindow,this->enemy,this->bomb,this->coin,this->scorePointer,this->coinsPointer);
        this->stats.updateText(this->plane,this->scorePointer,this->coinsPointer);
    }

    //endgame condition / warunek koñca gry
    if (this->plane.hp <= 0)
    {
        saveStats();
        saveTheHighestScore();
        this->endGame = true;
    }
        
}

void Game::render(sf::RenderWindow& mainWindow)
{
    //delete old frame / usuwanie starej klatki
    mainWindow.clear();
    
    //rendering background texture / renderowanie textur t³a
    mainWindow.draw(this->backGroundSprite);

    //rendering obcjets / renderowanie obiektów
    this->enemy.rederEnemies(mainWindow);
    this->bomb.rederBomb(mainWindow);
    this->coin.renderCoins(mainWindow);
    this->plane.renderPlane(mainWindow);
    this->stats.renderText(mainWindow);

    //display / wyœwietlanie
    mainWindow.display();
}


