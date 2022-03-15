#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Player
{
private:
	sf::RectangleShape shape;
	
	float vel;
	int hp;
	int hpMAX;

	void initVars();
	void initShape();
public:
	Player(float x = 0.f,float y = 0.f);
	~Player();

	//ACCESSORS
	const sf::RectangleShape& getShape() const;
	const int& getHP() const;
	const int& getHPMAX() const;

	//FUNCTIONS
	void takeDamage(const int damage);
	void gainHealth(const int health);

	void tickInput();
	void tickWindowCollision(sf::RenderTarget* target);
	void tick(sf::RenderTarget *target);
	void draw(sf::RenderTarget *target);
};

