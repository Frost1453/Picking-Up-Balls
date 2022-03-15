#include "Game.h"
#include "Player.h"

void Game::initVars()
{
	this->endGame = false;
	this->spawnTimerMAX = 10.f;
	this->spawnTimer = this->spawnTimerMAX;
	this->maxSwagBalls = 10;
	this->points = 0;
}

void Game::initWindow()
{
	this->videoMode = sf::VideoMode(800, 600);
	this->window = new sf::RenderWindow(this->videoMode, "Game", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
}

void Game::initFonts()
{
	if (!this->font.loadFromFile("Fonts/PixellettersFull.ttf"))
	{
		std::cout << " ! ERROR::GAME::INITFONTS::COULD NOT LOAD PixellettersFull.ttf" << std::endl;
	}

}

void Game::initText()
{
	// GUI TEXT INIT
	this->guiText.setFont(this->font);
	this->guiText.setFillColor(sf::Color::White);
	this->guiText.setCharacterSize(32);
	this->guiText.setString("test");

	// END GAME TEXT
	this->endGameText.setFont(this->font);
	this->endGameText.setFillColor(sf::Color::Red);
	this->endGameText.setCharacterSize(60);
	this->endGameText.setPosition(sf::Vector2f(100, 250));
	this->endGameText.setString("YOU ARE DEAD, EXIT GAME");
	this->endGameText.setOutlineColor(sf::Color::White);
	this->endGameText.setOutlineThickness(3.f);
}

Game::Game()
{
	this->initVars();
	this->initWindow();
	this->initFonts();
	this->initText();
}

Game::~Game()
{
	delete this->window;
}

const bool& Game::getEndGame() const
{
	return this->endGame;
}

	// FUNCTIONS

const bool Game::isRunning() const
{
	return this->window->isOpen()  
			//&& !this->endGame 
			;
}

void Game::spawnSwagBalls()
{
	// TIMER
	if (this->spawnTimer < this->spawnTimerMAX)
		this->spawnTimer += 1.f;
	else
	{
		if (this->swagBalls.size() < this->maxSwagBalls) 
		{
			this->swagBalls.push_back(SwagBall(*this->window, this->randBallType()));	

			this->spawnTimer = 0.f;
		}
	}
	
}

const int Game::randBallType() const
{
	int type = SwagBallTypes::DEFAULT;

	int randVal = rand() % 100 + 1;
	if (randVal > 60 && randVal < 80)
		type = SwagBallTypes::DAMAGING;
	else if (randVal > 80 && randVal <= 100)
		type = SwagBallTypes::HEALING;

	return type;
}

void Game::tickPlayer()
{
	this->player.tick(this->window);
	if (this->player.getHP() <= 0)
		this->endGame = true;
}

void Game::tickCollisions()
{
	// CHECK THE COLLISION
	for (size_t i = 0; i < this->swagBalls.size(); i++)
	{
		if (this->player.getShape().getGlobalBounds().intersects(this->swagBalls[i].getShape().getGlobalBounds()))
		{
			switch (this->swagBalls[i].getType()) 
			{
			case SwagBallTypes::DEFAULT:
				this->points++;
				break;
			case SwagBallTypes::DAMAGING:
				this->player.takeDamage(1);
				break;
			case SwagBallTypes::HEALING:
				this->player.gainHealth(1);
				break;
			}

			// ADD POINTS
			//this->points++;

			//REMOVE THE BALLS
			this->swagBalls.erase(this->swagBalls.begin() + i);
		}
	}
}

void Game::tickGUI()
{
	std::stringstream ss;

	ss << "Points: " << this->points << std::endl
		<< "Health: " << this->player.getHP() << "/" << this->player.getHPMAX() << std::endl;

	this->guiText.setString(ss.str());
}

void Game::tick()
{
	this->pollEvents();

	if (!this->endGame) {
		this->spawnSwagBalls();
		this->tickPlayer();
		this->tickCollisions();
		this->tickGUI();
	}
}

void Game::drawGUI(sf::RenderTarget* target)
{
	target->draw(this->guiText);
}

void Game::draw()
{
	// CLEAR
	this->window->clear(sf::Color::Black);

	// DRAW
	this->player.draw(this->window);

	for (auto i : this->swagBalls) 
	{
		i.draw(*this->window);
	}

	// DRAW GUI
	this->drawGUI(this->window);

	// DRAW END TEXT
	if (this->endGame)
		this->window->draw(this->endGameText);

	// SHOW
	this->window->display();
}