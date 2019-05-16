#include "world.h"



World::World(sf::Vector2u size)
{
	blockSize = 16;
	windSize = size;
	respawnApple();
	mAppleShape.setFillColor(sf::Color::Yellow);
	mAppleShape.setRadius(blockSize / 2);

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
	

}

void World::Render(sf::RenderWindow& target)
{
	target.draw(mAppleShape);
	for (int i=0;i<4;++i)
		target.draw(mWorldBounds[i]);
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



