#include "Snake.h"



Snake::Snake(int l_blockSize)
	: blockSize(l_blockSize)
{
	bodyRect.setSize(sf::Vector2f(blockSize - 1, blockSize - 1));
	Reset();
}

void Snake::setDirection(Direction l_dir)
{
	dir = l_dir;
}

Snake::Direction Snake::getDirection()
{
	return dir;
}

bool Snake::isAlive()
{
	return alive;
}

void Snake::toggleAlive()
{
	alive = !alive;
}

void Snake::setSpeed(int speed)
{
	mVelocity = speed;
}

int Snake::getVelocity()
{
	return mVelocity;
}

void Snake::Reset()
{
	mSnakeBody.clear();

	mSnakeBody.push_back(SnakeSegment(5, 6));
	mSnakeBody.push_back(SnakeSegment(5, 7));
	mSnakeBody.push_back(SnakeSegment(5, 8));

	setDirection(Direction::NONE);
	mLives = 3;
	mScore = 0;
	alive = true;
	mVelocity = 15;
}

void Snake::Cut(int segments)
{
	for (int i = 0; i < segments; i++)
		mSnakeBody.pop_back();
	   --mLives;
	if (!mLives) {
		lose();
		return;
	}

}

void Snake::Extend()
{
	if (mSnakeBody.empty()) return;
    SnakeSegment& snakeHead = mSnakeBody[mSnakeBody.size() - 1];

	if (mSnakeBody.size() > 1) {
		SnakeSegment& snakeTail = mSnakeBody[mSnakeBody.size() - 2];
		if (snakeTail.position.x == snakeHead.position.x) {
			if (snakeHead.position.y > snakeTail.position.y) {
				mSnakeBody.push_back(SnakeSegment(snakeHead.position.x, snakeHead.position.y + 1));
			}
			else 
			  mSnakeBody.push_back(SnakeSegment(snakeHead.position.x, snakeHead.position.y - 1));
		}
		else if (snakeHead.position.y == snakeTail.position.y) {
			if (snakeHead.position.x > snakeTail.position.x) {
				mSnakeBody.push_back(SnakeSegment(snakeHead.position.x+1, snakeHead.position.y));
			}
			else
				mSnakeBody.push_back(SnakeSegment(snakeHead.position.x-1, snakeHead.position.y));
		}
	}
	else {
		if(dir == Direction::Up)
			mSnakeBody.push_back(SnakeSegment(snakeHead.position.x, snakeHead.position.y + 1));
		else if(dir==Direction::Down)
			mSnakeBody.push_back(SnakeSegment(snakeHead.position.x, snakeHead.position.y - 1));
		else if(dir==Direction::Left)
			mSnakeBody.push_back(SnakeSegment(snakeHead.position.x+1, snakeHead.position.y));
		else if(dir==Direction::Right)
			mSnakeBody.push_back(SnakeSegment(snakeHead.position.x - 1, snakeHead.position.y));
	}
}

void Snake::Update()
{
	if (mSnakeBody.empty()) return;
	if (dir == Direction::NONE) return;
	move();
	checkCollision();
}

void Snake::Render(sf::RenderWindow& target)
{
	if (mSnakeBody.empty()) return;

	auto head = mSnakeBody.begin();
	bodyRect.setFillColor(sf::Color::Red);
	bodyRect.setPosition(head->position.x * blockSize, head->position.y * blockSize);
	target.draw(bodyRect);

	bodyRect.setFillColor(sf::Color(188));
	for (auto itr = mSnakeBody.begin() + 1; itr < mSnakeBody.end(); ++itr) {
		bodyRect.setPosition(itr->position.x * blockSize, itr->position.y * blockSize);
		target.draw(bodyRect);
	}
}

sf::Vector2i Snake::getPosition()
{
	return (!mSnakeBody.empty() ? mSnakeBody.front().position : sf::Vector2i(1, 1));
}

int Snake::getLives()
{
	return mLives;
}

int Snake::getScore()
{
	return mScore;
}

void Snake::increaseScore()
{
	mScore += 10;
}

void Snake::move()
{
	for (int i = mSnakeBody.size() - 1; i > 0; --i) {
		mSnakeBody[i].position = mSnakeBody[i - 1].position;
	}
	if (dir == Direction::Down)
		++mSnakeBody[0].position.y;
	if (dir == Direction::Up)
		--mSnakeBody[0].position.y;
	if (dir == Direction::Left)
		--mSnakeBody[0].position.x;
	if (dir == Direction::Right)
		++mSnakeBody[0].position.x;
}

void Snake::lose()
{
	alive = false;
}

void Snake::checkCollision()
{ 
	if (mSnakeBody.size() < 5) return;
	SnakeSegment& head = mSnakeBody.front();
	for (auto itr = mSnakeBody.begin()+1; itr < mSnakeBody.end(); ++itr) {
		if (itr->position == head.position) {
			int seg = mSnakeBody.end() - itr;
			Cut(seg);
			break;
		}
	}

}




SnakeSegment::SnakeSegment(int x, int y)
	: position(x,y)
{
}
