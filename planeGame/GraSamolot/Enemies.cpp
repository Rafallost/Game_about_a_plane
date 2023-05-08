#include "Enemies.h"


//constructor and destructor 
Enemies::Enemies()
{
	this->initEnemies();
	this->initVariables();
}

Enemies::~Enemies()
{

}

//init 
void Enemies::initEnemies()
{
    if(!this->enemyTextureBird.loadFromFile("assets/birdsmall.png"))
        std::cout << "ERROR::GAME::INITFONTS Fail do load Texture: assets/bird.png!" << std::endl;
    if(!this->enemyTextureRock.loadFromFile("assets/rock.png"))
        std::cout << "ERROR::GAME::INITFONTS Fail do load Texture: assets/rock.png!" << std::endl;
    if(!this->enemyTextureBigplane.loadFromFile("assets/plane_machine_big1.png"))
        std::cout << "ERROR::GAME::INITFONTS Fail do load Texture: assets/plane_machine_big1.png!" << std::endl;

    this->enemySpriteBird.setTexture(this->enemyTextureBird);
    this->enemySpriteRock.setTexture(this->enemyTextureRock);
    this->enemySpriteBigplane.setTexture(this->enemyTextureBigplane);
    this->enemySpriteRock.setScale(0.5f, 0.5f);
    this->enemySpriteBird.setScale(0.5f, 0.5f);

}

void Enemies::initVariables()
{
	this->enemySpawnTimerMax = 10.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->enemyMax = 2;
    this->enemiesSpeed = 8.f;
}

//Spawingn functions
void Enemies::spawnEnemy(sf::RenderTarget* window)
{
/* Spawning Enemies / pojawianie siê przeciwników
    -sets a random position / ustawia randomow¹ pozycje na ekranie
    -sets a random texture / ustawia randomow¹ teksturê
    -Adds enemies do the vector / dodaje przeciwników do vektora
 */
 //positioning / pozycjonowanie 

    int random = rand() % 5;
    switch (random)
    {
    case 0:
    case 1:
    case 2: 
        this->enemySpriteRock.setPosition(window->getSize().x,
            static_cast<float>(rand() % static_cast<int>(50.f - window->getSize().y)));

        //spawning enemy
        this->enemiesSprites.push_back(this->enemySpriteRock);
        break;
    case 3:
        this->enemySpriteBird.setPosition(window->getSize().x,
            static_cast<float>(rand() % static_cast<int>(50.f - window->getSize().y)));

        //spawning enemy
        this->enemiesSprites.push_back(this->enemySpriteBird);
        break;
    case 4:
        this->enemySpriteBigplane.setPosition(window->getSize().x,
            static_cast<float>(rand() % static_cast<int>(200.f - window->getSize().y)));

        //spawning enemy
        this->enemiesSprites.push_back(this->enemySpriteBigplane);
        break;
    }
}

//updating
void Enemies::updateEnemies(sf::RenderTarget* window)
{
    /*

Updates the enemy timer and spawns enemies
when total amount of enemies is smaller that maxium
moves the enemies downwards.
Removing the enemies at the edge of the screen 
*/

//updating the timer for enemy spawning
    if (this->enemiesSprites.size() < this->enemyMax)
    {
        if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
        {
            //spawn the enemy and reset the timer 

            this->spawnEnemy(window);
            this->enemySpawnTimer = 0.f;
        }
        else
            this->enemySpawnTimer += 1.f;
    }

    //moving and updating enemies
    for (int i = 0; i < this->enemiesSprites.size(); i++)
    {
        bool deleted = false;

        this->enemiesSprites[i].move(-(this->enemiesSpeed), 0.f);


        if (this->enemiesSprites[i].getPosition().x < -50)
        {
            this->enemiesSprites.erase(this->enemiesSprites.begin() + i);
        }

    }
}

//rendering
void Enemies::rederEnemies(sf::RenderTarget& target)
{
	for (auto& e : enemiesSprites)
	{
		target.draw(e);
	}
}
