#include "Game.h"



Game::Game() : mWindow(sf::VideoMode(600, 400), "Snake")
{
}

void Game::Run()
{
	sf::Clock clock;
	const sf::Time timePerFrame = sf::seconds(1 / 60);
	sf::Time dT = sf::Time::Zero;
	sf::Time timeSinceLastUpdate;
	while (mWindow.isOpen()) {
		sf::Time dt = clock.restart();
		timeSinceLastUpdate += dt;
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;

			processEvents();
			Update(timePerFrame);			
		}
		Render();
	}
}

void Game::Update(sf::Time dT)
{
}

void Game::Render()
{
}

void Game::processEvents()
{
}


