#include "Game.h"



Game::Game() : mWindow(sf::VideoMode(800, 600), "Snake"),
               mWorld(sf::Vector2u(800,600)),
               mPlayer(mWorld.getBlockSize())
{
}

void Game::Run()
{
	sf::Clock clock;
	
		sf::Time dt = sf::seconds(1.f / mPlayer.getVelocity()); // Modify this to change physics rate.
		sf::Time accumulator = sf::Time::Zero;
	
	while (mWindow.isOpen()) {
		accumulator += clock.getElapsedTime();
		clock.restart();
			while (accumulator >= dt)
			{
				processEvents();
				Update();
				accumulator -= dt;
			}
			Render();
	}
}


void Game::Update()
{
	mWorld.Update(mPlayer);
	mPlayer.Update();
	if (!mPlayer.isAlive())
		mPlayer.Reset();
}

void Game::Render()
{
	mWindow.clear(sf::Color::White);
	mWorld.Render(mWindow);
	mPlayer.Render(mWindow);
	mWindow.display();
}

void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event)) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)&&mPlayer.getDirection()!=Snake::Direction::Left)
			mPlayer.setDirection(Snake::Direction::Right);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && mPlayer.getDirection() != Snake::Direction::Right)
			mPlayer.setDirection(Snake::Direction::Left);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && mPlayer.getDirection() != Snake::Direction::Down)
			mPlayer.setDirection(Snake::Direction::Up);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && mPlayer.getDirection() != Snake::Direction::Up)
			mPlayer.setDirection(Snake::Direction::Down);
		if (event.type == sf::Event::Closed)
			mWindow.close();
	}
}


