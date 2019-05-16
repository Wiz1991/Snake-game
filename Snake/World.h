#pragma once
#include "Snake.h"
#include <random>
class World
{
public:
	World(sf::Vector2u size);
	void Update(Snake& player);
	void Render(sf::RenderWindow& target);

	int getBlockSize();
	void respawnApple();
	

private:
	sf::Vector2u windSize;
	sf::Vector2f mApple;
	int blockSize;
	

	sf::CircleShape mAppleShape;
	sf::RectangleShape mWorldBounds[4];

};

