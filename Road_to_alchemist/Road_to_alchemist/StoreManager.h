#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

typedef struct {
	int id; // -99 = null, 
	int quantity; // number of potion to pass
	float craftingTime;
	float timeLeft;
	int bonus; // 0 = no bonus, 1 = add time, 2 = move speed
	int score;

	// global position where menu ui placed
	int x;
	int y;

	// Bar -> timeLeft of menu
	int maxWidthBar;
	sf::IntRect rectBar;
	sf::Texture textureBar;
	sf::Sprite spriteBar;

	// BG of menu of 3 types based on bonus
	sf::Texture textureBarBG;
	sf::Sprite spriteBarBG;

	// potion -> based on id
	sf::Texture textureProduct;
	sf::Sprite spriteProduct;
} ListMenu;

class StoreManager
{
private:
	int maxMenu;
	float elapsedTime = 0.0f;
	float nextMenuTime;
	sf::Clock clock;

	void initShape(float x, float y);
	void initVariable();
public:
	StoreManager(float x, float y); // init store position to let player put potion in it
	~StoreManager();

	void generateMenu(); // generate new menu in random of id and bonus
	void placeMenu(); // player called -> send potion

	void update(); // update timer to generateMenu()
	void render(sf::RenderTarget& target);

};

