#pragma once

#include <iostream>
#include <ctime>
#include <vector>
#include <sstream>

#include "Player.h"
#include "SwagBall.h"



class Game
{
private:
	sf::VideoMode videoMode;
	sf::RenderWindow* window;
	bool endGame;
	sf::Event sfmlEvent;

	Player player;

	int points;

	sf::Font font;
	sf::Text guiText;
	sf::Text endGameText;

	std::vector<SwagBall> swagBalls;
	float spawnTimerMAX;
	float spawnTimer;
	int maxSwagBalls;

	void initVars();
	void initWindow();
	void initFonts();
	void initText();

public:
	// CONSTRUCTOR / DESTRUCTOR
	Game();
	~Game();

	//ACCESSORS
	const bool& getEndGame() const;

	//MODIFIERS

	//FUNCTIONS

	const bool isRunning() const;
	void pollEvents()
	{
		while (this->window->pollEvent(this->sfmlEvent))
		{
			switch (this->sfmlEvent.type)
			{
			case sf::Event::Closed:
				this->window->close();
				break;
			case sf::Event::KeyPressed:
				if (this->sfmlEvent.key.code == sf::Keyboard::Escape)
					this->window->close();
				break;
			}
		}
	}

	void spawnSwagBalls();
	const int randBallType() const;
	void tickPlayer();
	void tickCollisions();
	void tickGUI();
	void tick();

	void drawGUI(sf::RenderTarget* target);
	void draw();
};

