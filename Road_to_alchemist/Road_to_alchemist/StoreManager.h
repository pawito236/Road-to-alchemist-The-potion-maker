#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <vector>
#include <algorithm>

typedef struct {
	int id; // -99 = null, 
	int quantity; // number of potion to pass
	float craftingTime;
	float timeLeft;
	int bonus; // 0 = no bonus, 1 = add time, 2 = move speed
	int score;

	// global position where customer stand
	float x;
	float y;

	float currentX;
	float currentY;
	float speed;

	// Bar -> timeLeft of menu
	int maxWidthBar;
	sf::IntRect rectBar;
	sf::Texture textureBar;
	sf::Sprite spriteBar;

	// Customer of 3 types based on bonus
	sf::IntRect rectSourceSprite;
	sf::Texture textureCustomer;
	sf::Sprite spriteCustomer;

	// potion -> based on id
	sf::Texture textureProduct;
	sf::Sprite spriteProduct;


} ListMenu;

typedef struct {

	int bonus; // 0 = no bonus, 1 = add time, 2 = move speed
	int score;

} ListRevenue;

class StoreManager
{
private:
	int maxMenu;
	float elapsedTime = 0.0f;
	float nextMenuTime;

	//ListMenu listMenu[5] = {};

	// For Store instanec
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Clock clock;
	sf::IntRect rectSourceSprite;

	std::vector<ListMenu> listMenu;

	void initShape(float x, float y);
	void initVariable();
public:
	StoreManager(float x, float y); // init store position to let player put potion in it
	~StoreManager();

	void generateMenu(); // generate new menu in random of id and bonus
	std::vector<ListRevenue> placeMenu(int potion); // player called -> send potion

	const sf::Sprite& getSprite() const;

	void update(); // update timer to generateMenu()
	void render(sf::RenderTarget& target);
};

