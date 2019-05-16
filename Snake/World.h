#pragma once
#include "Snake.h"
class World
{
public:
	World();
	void update(sf::Time dt);
	void Render();
	

private:
	Snake* mSnake;
};

