#include "Plane.h"
#include "Bombs.h"
#include "Enemies.h"
#include "Game.h"

//konstructor and destructor / konstruktor i destruktor
Plane::Plane()
{
    //initializing / inicjalizowanie 
	this->initPlane();
	this->initVariables();
   
}

Plane::~Plane()
{

}

//initializing / inicjalizowanie 
void Plane::initPlane()
{
    if(!this->planeTexture.loadFromFile("assets/planelesssflamy1.png"))
        std::cout << "ERROR::GAME::INITFONTS Fail do load Texture: assets/planelesssflamy1.png!" << std::endl;
    
    if (!this->boomTexture.loadFromFile("assets/boom.png"))
        std::cout << "ERROR::GAME::INITFONTS Fail do load Texture: assets/planelesssflamy1.png!" << std::endl;
    
    this->planeSprite.setTexture(this->planeTexture);
	this->planeSprite.setPosition(100.f, 540.f);
    this->planeSprite.setScale(this->scaleOfPlane, this->scaleOfPlane);

}

void Plane::initVariables()
{
    this->planeSizeX = 289.f;
    this->planeSizeY = 98.f;
    this->hpPointer = &hp;
}

//updating / akutalizacja 
void Plane::updatePlane(sf::RenderWindow& mainWindow, Enemies& enemy, Bombs& bomb, Coins& coin, unsigned* score, int* coinsPointer)
{
    //plane movement / poruszanie siê samolotu

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        if (this->planeSprite.getPosition().y <= 0.f)
        {
            this->planeSprite.move(0.f, 0.f);
            this->planeSprite.setRotation(0.f);
        }
        else
        {
            this->planeSprite.move(0.f, -(this->speedLvl));
            this->planeSprite.setRotation(-15.f);
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        if ((this->planeSprite.getPosition().y + ( (this->planeSizeY) * (this->scaleOfPlane) )) >= mainWindow.getSize().y)
        {
            this->planeSprite.move(0.f, 0.f);
            this->planeSprite.setRotation(0.f);
        }
        else
        {
            this->planeSprite.move(0.f, (this->speedLvl));
            this->planeSprite.setRotation(10.f);
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        if (this->planeSprite.getPosition().x <= 0.f)
        {
            this->planeSprite.move(0.f, 0.f);
            this->planeSprite.setRotation(0.f);
        }
        else
        {
            this->planeSprite.move(-(this->speedLvl), 0.f);
            this->planeSprite.setRotation(0.f);
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        if ((this->planeSprite.getPosition().x + ((this->planeSizeX) * (this->scaleOfPlane)) >= mainWindow.getSize().x))
        {
            this->planeSprite.move(0.f, 0.f);
            this->planeSprite.setRotation(0.f);
        }
        else
        {
            this->planeSprite.move((this->speedLvl), 0.f);
            this->planeSprite.setRotation(0.f);
        }
    }

    //Collision / kolizja
    if (timeFromHit.getElapsedTime().asSeconds() < 1.f)
    {
        //protection after hit and changing color /
        //ochrona po uderzniu i zmaiana koloru
        planeSprite.setColor(sf::Color(128,128,128,60));
    }
    else
    {
        //returning to color before / powrót do poprzedniego koloru
        planeSprite.setColor(sf::Color(255,255,255,255));

        //Enemies collision / kolizja z przeciwnikami 
        for (int i = 0; i < enemy.enemiesSprites.size(); i++)
        {
            if (this->planeSprite.getGlobalBounds().intersects(enemy.enemiesSprites[i].getGlobalBounds()))
            {
                this->hp -= 1;
                enemy.enemiesSprites.erase(enemy.enemiesSprites.begin() + i);
                timeFromHit.restart();

            }
        }

        //bombs colision / kolizja z bombami 
        for (int i = 0; i < bomb.bombsSprites.size(); i++)
        {
            if (this->planeSprite.getGlobalBounds().intersects(bomb.bombsSprites[i].getGlobalBounds()))
            {
                this->hp -= 2;
               
                bomb.bombsSprites.erase(bomb.bombsSprites.begin() + i);
                timeFromHit.restart();
                  
            }
        }
    }
    if (timeFromCoin.getElapsedTime().asSeconds() > 0.3f)
    {
        //coins colision / kolizja z monetkami
        for (int i = 0; i < coin.coinsSprites.size(); i++)
        {
            if (this->planeSprite.getGlobalBounds().intersects(coin.coinsSprites[i].getGlobalBounds()))
            {
                *score += 100;
                *coinsPointer += 1;

                coin.coinsSprites.erase(coin.coinsSprites.begin() + i);
                timeFromCoin.restart();

            }
        }
    }
   
   
}

//render / renderowanie
void Plane::renderPlane(sf::RenderTarget& target)
{
    target.draw(this->planeSprite);
}
