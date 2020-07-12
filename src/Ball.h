#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>

using namespace sf;
using namespace std;

class Ball
{
private:
	Vector2f m_Position;
	RectangleShape m_Shape;

	float m_Speed = 1000.0f;
	float m_DirectionX = .2f;
	float m_DirectionY = .2f;

public:
	Ball(float startX, float startY);

	FloatRect getPosition();

	RectangleShape getShape();

	float getXVelocity();

	void reboundSides();

	void reboundLeftSide(ofstream &iFile);

	void reboundRightSide(ofstream &iFile);

	void reboundBatOrTop(ofstream &iFile);

	void reboundBottom(ofstream &iFile);

	void reboundTop(ofstream &iFile);

	void hitBottom(ofstream &iFile);

	void reboundBat(ofstream &iFile);

	void update(Time, ofstream &iFile);
};
