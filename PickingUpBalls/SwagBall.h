#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

enum SwagBallTypes {DEFAULT = 0, DAMAGING, HEALING, NROFTYPES};

class SwagBall
{
private:
	sf::CircleShape shape;
	int type;

	void initShape(const sf::RenderWindow &window);
public:
	SwagBall(const sf::RenderWindow& window, int type);
	~SwagBall();

	//ACCESSOR
	const sf::CircleShape getShape() const;
	const int& getType() const;


	// FUNCTIONS
	void tick();
	void draw(sf::RenderTarget &target);
};

