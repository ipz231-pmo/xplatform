#pragma once
#include <vector>

struct Point
{
	int x, y;
};

class Game
{
public:
	Game();
	void update(float deltaTime);
	std::vector<Point>& getTail() const;
	Point getHead() const;
	bool isGameOver() const;
private:
	void _move();
	Point _head;
	std::vector<Point> _tail;
	bool _gameOver, _left, _top;
	float _timeAccumulated;
	const float _TIME_STEP = 500;
};
