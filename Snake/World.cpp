#include "world.h"



World::World(sf::Vector2u size)
	: mFont()
	, mScore()
	, mLives()
{
	blockSize = 16;
	windSize = size;
	respawnApple();
	mAppleShape.setFillColor(sf::Color::Yellow);
	mAppleShape.setRadius(blockSize / 2);
	//Generate world bounds
	for (int i = 0; i < 4; ++i) {
		mWorldBounds[i].setFillColor(sf::Color(150,0,0));
		if (!((i + 1) % 2)) {
			mWorldBounds[i].setSize(sf::Vector2f(size.x, blockSize));
		}
		else mWorldBounds[i].setSize(sf::Vector2f(blockSize, size.y));
		if (i < 2) 
			mWorldBounds[i].setPosition(0, 0);
		else {
			mWorldBounds[i].setPosition(sf::Vector2f(size));
			mWorldBounds[i].setOrigin(mWorldBounds[i].getSize());
		}
		
	}
	mFont.loadFromFile("micross.ttf");
	mScore.setFont(mFont);
	mLives.setFont(mFont);

	mScore.setCharacterSize(15);
	mScore.setFillColor(sf::Color::Black);
	mScore.setPosition(windSize.x - blockSize - 80, windSize.y - blockSize - 20);
	
	mLives.setCharacterSize(15);
	mLives.setFillColor(sf::Color::Black);
	mLives.setPosition(windSize.x - blockSize - 80, windSize.y - blockSize - 40);
	


}

void World::Update(Snake& player)
{
	if (player.getPosition().x == mApple.x && player.getPosition().y == mApple.y) {
		player.Extend();
		player.increaseScore();
		respawnApple();
	}
	int gridSize_x = windSize.x / blockSize;
	int gridSize_y = windSize.y / blockSize;

	if(player.getPosition().x <= 0 || player.getPosition().y <= 0 || player.getPosition().y>=gridSize_y-1 || player.getPosition().x >= gridSize_x-1)
		player.lose();
	std::string lstring = "Lives: " + std::to_string(player.getLives());
	std::string sstring = "Score: " + std::to_string(player.getScore());
	mScore.setString(sstring);
	mLives.setString(lstring);

}

void World::Render(sf::RenderWindow& target)
{
	target.draw(mAppleShape);
	for (int i=0;i<4;++i)
		target.draw(mWorldBounds[i]);
	
	target.draw(mScore);
	target.draw(mLives);
}

int World::getBlockSize()
{
	return blockSize;
}

void World::respawnApple()
{
	int maxX = (windSize.x / blockSize)-2;
	int maxY = (windSize.y / blockSize)-2;
	mApple = sf::Vector2f(rand() % maxX + 1, rand() % maxY + 1);
	mAppleShape.setPosition(mApple.x*blockSize,mApple.y*blockSize);
}





