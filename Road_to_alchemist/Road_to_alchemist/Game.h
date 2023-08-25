#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Player.h"
#include "CraftingTable.h"
#include "IngredientBox.h"
#include <iostream>
#include <ctime>

#include <vector>
#include <sstream>


class Game
{
private:
	sf::VideoMode videoMode;
	sf::RenderWindow* window;
	bool endGame;
	sf::Event sfmlEvent;

	sf::Texture texture;
	sf::Sprite sprite;

	Player player;

	

	void initVariable();
	void initWindow();


public:
	std::vector<CraftingTable> craftingTable;
	std::vector<IngredientBox> ingredientBox;

	//Constructors and Destructor
	Game();
	~Game();

	//Accessors


	//Modifier

	//Function
	void poolEvents();
	void spawnMapItem();
	void updatePlayer();
	void update();
	bool running();

	void render();
};

