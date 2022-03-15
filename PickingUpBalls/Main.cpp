#include "Game.h"

int main() {


	//INITIALIZE RANDOM SEED

	srand(static_cast<unsigned>(time(0)));

	// INITIALIZE GAME OBJECT

	Game game;

	// GAME LOOP

	while (game.isRunning()) 
	{
		game.tick();
		game.draw();
	}

	return 0;
}