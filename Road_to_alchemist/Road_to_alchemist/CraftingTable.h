#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

enum CraftingTableTypes {TIER1 = 0, TIER2};

typedef struct {
	int id;
} ListIngredient;

class CraftingTable
{
private:
	sf::CircleShape shape;
	int type;
	int combination_id;
	bool combinationStatus;
	float elapsedTime = 0.0f;
	int temp_combination_id;

	float craftingTime;
	sf::Clock clockcraftingTime;

	int maxWidthBar;
	sf::IntRect rectBar;
	sf::Texture textureBar;
	sf::Sprite spriteBar;
	sf::Texture textureBarBG;
	sf::Sprite spriteBarBG;

	sf::Texture textureProduct;
	sf::Sprite spriteProduct;
	sf::Texture textureProductBorder;
	sf::Sprite spriteProductBorder;

	sf::Texture textureItem1;
	sf::Sprite spriteItem1;
	sf::Texture textureItem2;
	sf::Sprite spriteItem2;
	sf::Texture textureBorder1;
	sf::Sprite spriteBorder1;
	sf::Texture textureBorder2;
	sf::Sprite spriteBorder2;

	sf::Texture texture;
	sf::Sprite sprite;
	sf::Clock clock;
	sf::IntRect rectSourceSprite;


	void initShape(float x, float y);

	void initVariable();

public:
	CraftingTable(int type, float x, float y);
	~CraftingTable();

	//Acesstor
	const int& getType() const;
	const sf::Sprite& getSprite() const;

	void update();
	void render(sf::RenderTarget& target);

	bool is_crafting;
	ListIngredient listIngredient[2] = {
	{-99},
	{-99}
	};
	

	void resetCombination();
	int getCombinationID();

	void checkCombination();
	void startCrafting();

	void draw(sf::RenderWindow& window);
};

