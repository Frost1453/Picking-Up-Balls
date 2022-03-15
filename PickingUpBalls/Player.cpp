#include "Player.h"


	// INITIALIZATION
void Player::initVars()
{
	this->vel = 5.f;
	this->hpMAX = 10;
	this->hp = hpMAX;
}

void Player::initShape()
{
	this->shape.setFillColor(sf::Color::Green);
	this->shape.setSize(sf::Vector2f(50.f, 50.f));
}

	// CONSTRUCTOR / DESTRUCTOR
Player::Player(float x, float y)
{
	this->shape.setPosition(x, y);

	this->initVars();
	this->initShape();
}

Player::~Player()
{

}

	// ACCESSORS

const sf::RectangleShape& Player::getShape() const
{
	return this->shape;
}

const int& Player::getHP() const
{
	return this->hp;
}

const int& Player::getHPMAX() const
{
	return this->hpMAX;	
}

	// FUNCTIONS

void Player::takeDamage(const int damage)
{
	if (this->hp > 0)
		this->hp -= damage;

	if (this->hp < 0)
		this->hp = 0;
}

void Player::gainHealth(const int health)
{
	if (this->hp < this->hpMAX)
		this->hp += health;

	if (this->hp > this->hpMAX)
		this->hp = this->hpMAX;
}

void Player::tickInput()
{
	// KEYBOARD INPUT
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		this->shape.move(-this->vel, 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		this->shape.move(this->vel, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		this->shape.move(0.f, -this->vel);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		this->shape.move(0.f, this->vel);
	}

	// KEYBOARD INPUT
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		this->shape.move(-this->vel, 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		this->shape.move(this->vel, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{ 
		this->shape.move(0.f, -this->vel);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		this->shape.move(0.f, this->vel);
	}
}

void Player::tickWindowCollision(sf::RenderTarget* target)
{
	//LEFT
	if (this->shape.getGlobalBounds().left <= 0.f )
		this->shape.setPosition(0.f, this->shape.getGlobalBounds().top);
	
	//RIGHT
	if (this->shape.getGlobalBounds().left + this->shape.getGlobalBounds().width >= target->getSize().x)	
		this->shape.setPosition(target->getSize().x - this->shape.getGlobalBounds().width,this->shape.getGlobalBounds().top);
	
	//TOP
	if (this->shape.getGlobalBounds().top <= 0.f)	
		this->shape.setPosition(this->shape.getGlobalBounds().left, 0.f);
	
	//BOTTOM
	if (this->shape.getGlobalBounds().top + this->shape.getGlobalBounds().height >= target->getSize().y)
		this->shape.setPosition(this->shape.getGlobalBounds().left, target->getSize().y - this->shape.getGlobalBounds().height);
}


void Player::tick(sf::RenderTarget *target)
{

	// KEYBOARD INPUT
	this->tickInput();

	// WINDOW COLLISION 
	this->tickWindowCollision(target);
}

void Player::draw(sf::RenderTarget* target)
{
	target->draw(this->shape);
}

	
