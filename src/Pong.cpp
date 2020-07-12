// Pong.cpp : Defines the entry point for the console application.
//
#include "Bat.h"
#include "Ball.h"
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>

#include <fstream>
#include <iostream>
using namespace std;

int main()
{
	ofstream myfile;
	myfile.open("Pong.txt");
	myfile << "*** Start of Program ***" << endl;
	// Create a video mode object
	VideoMode vm(1920, 1080);

	// Create and open a window for the game

	RenderWindow window(vm, "Pong", Style::Fullscreen);

	int score = 0;
	int lives = 3;

	// Create a bat
	Bat bat(1920 / 2, 1080 - 20);

	// Create a ball
	Ball ball(1920 / 2, 0);

	// Create a Text object called HUD
	Text hud;

	// A cool retro-style font
	Font font;
	font.loadFromFile("fonts/DS-DIGI.ttf");

	// Set the font to our retro-style
	hud.setFont(font);

	// Make it nice and big
	hud.setCharacterSize(75);

	// Choose a color
	hud.setFillColor(Color::White);

	hud.setPosition(20, 20);

	// Here is our clock for timing everything
	Clock clock;

	while (window.isOpen())
	{
		/*
		Handle the player input
		*********************************************************************
		*********************************************************************
		*********************************************************************
		*/

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				// Quit the game when the window is closed
				window.close();
		}

		// Handle the player quitting
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		// Handle the pressing and releasing of the arrow keys
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			bat.moveLeft();
		}
		else
		{
			bat.stopLeft();
		}

		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			bat.moveRight();
		}
		else
		{
			bat.stopRight();
		}

		/*
		Update the bat, the ball and the HUD
		*********************************************************************
		*********************************************************************
		*********************************************************************
		*/
		// Update the delta time
		Time dt = clock.restart();
		bat.update(dt);
		ball.update(dt, myfile);
		// Update the HUD text
		std::stringstream ss;
		ss << "Score:" << score << "    Lives:" << lives;
		hud.setString(ss.str());

		// Handle ball hitting the bottom
		if (ball.getPosition().top > window.getSize().y)
		{
			myfile << "*** Ball hitting bottom ***" << endl;

			//ball.reboundBottom(myfile);
			ball.hitBottom(myfile);

			// Remove a life
			lives--;

			// Check for zero lives
			if (lives < 1)
			{
				// reset the score
				score = 0;
				// reset the lives
				lives = 3;
			}
		}

		// Handle ball hitting top
		if (ball.getPosition().top < 0)
		{
			myfile << "*** Ball hitting top ***" << endl;
			//ball.reboundBatOrTop(myfile);
			ball.reboundTop(myfile);

			// Add a point to the players score
			score++;
			myfile << "score = " << score << endl;
		}

		// Handle ball hitting sides
		if (ball.getPosition().left < 0)
		{
			myfile << "*** Ball hitting left side ***" << endl;
			ball.reboundLeftSide(myfile);
		}
		else if (ball.getPosition().left + 10 > window.getSize().x)
		{
			myfile << "*** Ball hitting right side ***" << endl;
			ball.reboundRightSide(myfile);
		}

		// Has the ball hit the bat?
		if (ball.getPosition().intersects(bat.getPosition()))
		{
			myfile << "*** Ball intersects Bat ***" << endl;
			// Hit detected so reverse the ball
			// Hit will be scored once this ball hits the top.
			ball.reboundBat(myfile);
		}
		/*
		Draw the bat, the ball and the HUD
		*********************************************************************
		*********************************************************************
		*********************************************************************
		*/
		window.clear();
		window.draw(hud);
		window.draw(bat.getShape());
		window.draw(ball.getShape());
		window.display();
	}

	myfile << "*** End of Program ***" << endl;
	myfile.close();
	return 0;
}
