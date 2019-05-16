#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#
#include "World.h"

class Game
{
public:
	Game();

	void Run();
	void Update();
	void Render();
	void processEvents();

private:
	sf::RenderWindow mWindow;
	World mWorld;
	Snake mPlayer;


	
};

