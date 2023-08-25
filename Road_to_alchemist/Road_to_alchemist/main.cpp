#include "Game.h"
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

int main() {
	//init random seed
	srand(static_cast<unsigned>(time(0)));

	//init game object
	Game game;

	//Game loop
	while (game.running())
	{
		game.update();
		game.render();
	}

	//End of app
	return 0;
}