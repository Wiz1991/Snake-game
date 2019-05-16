#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
class Game
{
public:
	Game();

	void Run();
	void Update(sf::Time dT);
	void Render();
	void processEvents();

private:
	sf::RenderWindow mWindow;



	
};

