#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

struct SnakeSegment {
	SnakeSegment(int x, int y);
	sf::Vector2i position;
};
typedef std::vector<SnakeSegment> SnakeContainer;


class Snake
{
public:
	enum class Direction {
		NONE,
		Left,
		Up,
		Right,
		Down
	};
	Snake(int l_blockSize);

	void setDirection(Direction l_dir);
	Direction getDirection();

	bool isAlive();
	void toggleAlive();

	void setSpeed(int speed);
	int getVelocity();

	void Reset();
	void Cut(int segments);
	void Extend();

	void Update();
	void Render(sf::RenderWindow& target);

	sf::Vector2i getPosition();
	int getLives();
	int getScore();
	void increaseScore();
	void move();
	void lose();

private:
	void checkCollision();
	SnakeContainer mSnakeBody;
	sf::RectangleShape bodyRect;
	int blockSize;
	bool alive;
	Direction dir;
	int mLives;
	int mVelocity;
	int mScore;
};

