#include "SwagBall.h"

void SwagBall::initShape(const sf::RenderWindow &window)
{
	this->shape.setRadius(static_cast<float>(rand() % 10 + 10));

	sf::Color color;

	switch (this->type)
	{
	case DEFAULT:
		color = sf::Color(rand()%255+1,rand()%255+1,rand()%255+1);
		break;
	case DAMAGING:
		color = sf::Color(110, 8, 8);
		this->shape.setOutlineColor(sf::Color::White);
		this->shape.setOutlineThickness(3.f);
		break;
	case HEALING:
		color = sf::Color::Green;
		this->shape.setOutlineColor(sf::Color::White);
		this->shape.setOutlineThickness(3.f);
		break;
	}

	this->shape.setFillColor(color);
	this->shape.setPosition(
		sf::Vector2f
		(static_cast<float>(rand() % window.getSize().x - this->shape.getGlobalBounds().width),
			static_cast<float>(rand() % window.getSize().y - this->shape.getGlobalBounds().height)
		)
	);
}

SwagBall::SwagBall(const sf::RenderWindow& window, int type)
	: type(type)
{
	this->initShape(window);
}

SwagBall::~SwagBall()
{

}

const sf::CircleShape SwagBall::getShape() const
{
	return this->shape;
}

const int& SwagBall::getType() const
{
	return this->type;
}

void SwagBall::tick()
{
	
}

void SwagBall::draw(sf::RenderTarget &target)
{
	target.draw(this->shape);
}
