#include "Coins.h"

Coins::Coins()
{
	this->initCoins();
	this->initVariables();
}

Coins::~Coins()
{

}

void Coins::initCoins()
{
    if(!this->coinTexture.loadFromFile("assets/bitcoin.png"))
        std::cout << "ERROR::GAME::INITFONTS Fail do load Texture: assets/bitcoin.png!" << std::endl;
    this->coinSprite.setTexture(this->coinTexture);
    this->coinSprite.setScale(0.5f,0.5f);
}

void Coins::initVariables()
{
    this->coinsSpeed = 8.f;
	this->coinSpawnMax = 15.f;
	this->coinSpawnTimer = this->coinSpawnMax;
	this->maxCoins = 5;
}

void Coins::spawnCoins(sf::RenderTarget* window)
{
	this->coinSprite.setPosition(window->getSize().x,
        static_cast<float>(rand() % static_cast<int>(50.f - window->getSize().y)));

	//spawning enemy
	this->coinsSprites.push_back(this->coinSprite);
}

void Coins::updateCoins(sf::RenderTarget* window)
{
    //pojawianie sie
    if (this->coinsSprites.size() < this->maxCoins)
    {
        if (this->coinSpawnTimer >= this->coinSpawnMax)
        {
            //spawn the enemy and reset the timer 

            this->spawnCoins(window);
            this->coinSpawnTimer = 0.f;
        }
        else
            this->coinSpawnTimer += 1.f;
    }

    //przemieszcanie i znikanie
    for (int i = 0; i < this->coinsSprites.size(); i++)
    {
        bool deleted = false;

        this->coinsSprites[i].move(-(this->coinsSpeed), 0.f);


        if (this->coinsSprites[i].getPosition().x < -50)
        {
            this->coinsSprites.erase(this->coinsSprites.begin() + i);
        }

    }
}

void Coins::renderCoins(sf::RenderTarget& target)
{
	for (auto& e : this->coinsSprites)
	{
		target.draw(e);

	}
}
