#include "Ball.h"
#include <iostream>

using namespace std;

// This the constructor function
Ball::Ball(float startX, float startY)
{
	m_Position.x = startX;
	m_Position.y = startY;

	m_Shape.setSize(sf::Vector2f(10, 10));
	m_Shape.setPosition(m_Position);
}

FloatRect Ball::getPosition()
{
	return m_Shape.getGlobalBounds();
}

RectangleShape Ball::getShape()
{
	return m_Shape;
}

float Ball::getXVelocity()
{
	return m_DirectionX;
}

void Ball::reboundSides()
{
	m_DirectionX = -m_DirectionX;
}

void Ball::reboundLeftSide(ofstream &iFile)
{
	iFile << "--> Ball::reboundLeftSide" << endl;
	iFile << "getPosition().left = " << getPosition().left << endl;
	iFile << "getPosition().top = " << getPosition().top << endl;
	m_DirectionX = -m_DirectionX;
	iFile << "m_DirectionX = " << m_DirectionX << endl;
	// Set x position of ball to zero because if it's currently negative,
	// it could stay negative for a while and bounce back and forth
	m_Position.x = 0;
	iFile << "m_Position.x set to 0" << endl;
	iFile << "<-- Ball::reboundLeftSide" << endl;
}

void Ball::reboundRightSide(ofstream &iFile)
{
	iFile << "--> Ball::reboundRightSide" << endl;
	iFile << "getPosition().left = " << getPosition().left << endl;
	iFile << "getPosition().top = " << getPosition().top << endl;
	m_DirectionX = -m_DirectionX;
	iFile << "m_DirectionX = " << m_DirectionX << endl;
	iFile << "<-- Ball::reboundRightSide" << endl;
}

void Ball::reboundBatOrTop(ofstream &iFile)
{
	iFile << "--> Ball::reboundBatOrTop" << endl;
	iFile << "getPosition().left = " << getPosition().left << endl;
	iFile << "getPosition().top = " << getPosition().top << endl;
	m_DirectionY = -m_DirectionY;
	iFile << "m_DirectionY = " << m_DirectionY << endl;
	iFile << "<-- Ball::reboundBatOrTop" << endl;
}

void Ball::reboundBat(ofstream &iFile)
{
	iFile << "--> Ball::reboundBat" << endl;
	iFile << "getPosition().left = " << getPosition().left << endl;
	iFile << "getPosition().top = " << getPosition().top << endl;
	m_DirectionY = -1.0f * abs(m_DirectionY);
	iFile << "m_DirectionY = " << m_DirectionY << endl;
	iFile << "<-- Ball::reboundBat" << endl;
}

void Ball::reboundTop(ofstream &iFile)
{
	iFile << "--> Ball::reboundTop" << endl;
	iFile << "getPosition().left = " << getPosition().left << endl;
	iFile << "getPosition().top = " << getPosition().top << endl;
	m_DirectionY = abs(m_DirectionY);
	// Set y position of ball to zero because if it's currently negative,
	// it could stay negative for a while and mess up the scoring
	m_Position.y = 0;
	iFile << "m_DirectionY = " << m_DirectionY << endl;
	iFile << "m_Position.y set to 0" << endl;
	m_Speed = m_Speed * 1.10f;
	if (m_Speed >= MAX_SPEED)
		m_Speed = MAX_SPEED;
	iFile << "m_Speed = " << m_Speed << endl;
	iFile << "<-- Ball::reboundTop" << endl;
}

void Ball::hitBottom(ofstream &iFile)
{
	iFile << "--> Ball::hitBottom" << endl;
	m_DirectionY = abs(m_DirectionY);
	m_Position.y = 0;
	m_Position.x = 500;
	m_Speed = 1000.0f;
	iFile << "<-- Ball::hitBottom" << endl;
}

void Ball::reboundBottom(ofstream &iFile)
{
	iFile << "--> Ball::reboundBottom" << endl;
	m_DirectionY = -m_DirectionY;
	m_Position.y = 0;
	m_Position.x = 500;
	iFile << "<-- Ball::reboundBottom" << endl;
}

void Ball::update(Time dt, ofstream &iFile)
{
	iFile << "--> Ball::update" << endl;
	// Update the ball position variables
	m_Position.x += m_DirectionX * m_Speed * dt.asSeconds();
	m_Position.y += m_DirectionY * m_Speed * dt.asSeconds();

	iFile << "Ball position after update: " << m_Position.x << ", "
			<< m_Position.y << endl;

	// Move the ball and the bat
	m_Shape.setPosition(m_Position);
	iFile << "<-- Ball::update" << endl;
}
