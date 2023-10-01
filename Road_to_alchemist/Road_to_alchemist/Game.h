#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Player.h"
#include "CraftingTable.h"
#include "IngredientBox.h"
#include "StoreManager.h"

#include <iostream>
#include <ctime>

#include <vector>
#include <sstream>
#include <cstdio>

typedef struct {

	int reputation;

} GameStatus;

class Game
{
private:
	sf::VideoMode videoMode;
	sf::RenderWindow* window;
	bool endGame;

	sf::Vector2i mousePosition;


	bool isMenu;
	sf::Texture textureMenu;
	sf::Sprite spriteMenu;
	bool isMenu2; // How to play
	sf::Texture textureMenu2;
	sf::Sprite spriteMenu2;
	bool isMenu3; // Leaderboard
	sf::Texture textureMenu3;
	sf::Sprite spriteMenu3;

	bool isMenu4; // Enter Name
	sf::Texture textureMenu4;
	sf::Sprite spriteMenu4;

	sf::Event sfmlEvent;

	sf::Texture texture;
	sf::Sprite sprite;

	Player player;

	int reputation;
	sf::Font font;
	sf::Text reputationText;

	sf::Text playerName;
	sf::String input;


	sf::SoundBuffer bufferCoin;
	sf::Sound soundCoin;
	sf::Music backgroundMusic;

	void initVariable();
	void initWindow();
	void initFont();
	void initText();

	void initMusic();

public:
	std::vector<CraftingTable> craftingTable;
	std::vector<IngredientBox> ingredientBox;

	std::vector<StoreManager> storeManager;

	//Constructors and Destructor
	Game();
	~Game();

	//Accessors


	//Modifier
	std::string getPlayerName();

	//Function
	void poolEvents();
	void spawnMapItem();
	void updatePlayer();
	void update();
	bool running();

	void updateGui();
	void renderGui(sf::RenderTarget* target);

	void render();
};

