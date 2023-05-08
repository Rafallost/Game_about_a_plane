#include "Bombs.h"
#include "Plane.h"

//konstruktor and destruktor
Bombs::Bombs()
{
	this->initBomb();
	this->initVariables();
}

Bombs::~Bombs()
{

}

//inicilizing
void Bombs::initBomb()
{
    if(!this->bombTexture.loadFromFile("assets/bomb.png"))
        std::cout << "ERROR::GAME::INITFONTS Fail do load Texture: assets/bomb.png!" << std::endl;
    this->bombSprite.setTexture(this->bombTexture);
}
void Bombs::initVariables()
{
	this->bombSpawnTimerMax = 500.f;
	this->bombSpawnTimer = this->bombSpawnTimerMax;
	this->bombMax = 0;
	this->bombsSpeed = 8.f;
    this->mouseHeld = false;
}

//spawning 
void Bombs::spawnBomb(sf::RenderTarget* window)
{
	//positioning
	this->bombSprite.setPosition(window->getSize().x,
		static_cast<float>(rand() % static_cast<int>(100.f - window->getSize().y)));

	//adding enemy
	this->bombsSprites.push_back(this->bombSprite);
}

//updating
void Bombs::updateBomb(sf::RenderTarget* window, sf::Vector2f mousePosView, unsigned* points, int* hp)
{
    if (this->bombsSprites.size() < this->bombMax)
    {
        if (this->bombSpawnTimer >= this->bombSpawnTimerMax)
        {
            //spawn the enemy and reset the timer 

            this->spawnBomb(window);
            this->bombSpawnTimer = 0.f;
        }
        else
            this->bombSpawnTimer += 1.f;
    }

    //moving and updating enemies
    for (int i = 0; i < this->bombsSprites.size(); i++)
    {
        bool deleted = false;

        this->bombsSprites[i].move(-(this->bombsSpeed), 0.f);


        if (this->bombsSprites[i].getPosition().x < -50)
        {
            this->bombsSprites.erase(this->bombsSprites.begin() + i);
             *hp -= 2;
        }

    }

    //check if clicked upon
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (this->mouseHeld == false)
        {
            this->mouseHeld = true;
            bool deleted = false;

            for (size_t i = 0; i < this->bombsSprites.size() && deleted == false; i++)
            {
                if (this->bombsSprites[i].getGlobalBounds().contains(mousePosView))
                {
                    //delete the enemy
                    deleted = true;
                    this->bombsSprites.erase(this->bombsSprites.begin() + i);

                    //gain points
                    *points += 200;
                }
            }
        }
    }
    else
    {
        this->mouseHeld = false;
    }

}

void Bombs::rederBomb(sf::RenderTarget& target)
{
    for (auto& e : this->bombsSprites)
    {
        target.draw(e);

    }
}
