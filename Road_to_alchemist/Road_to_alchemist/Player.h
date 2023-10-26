#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "CraftingTable.h"
#include "IngredientBox.h"
#include "StoreManager.h"

class Player
{
private:
	sf::RectangleShape shape;
	int hp;
	int hpMax;



	bool is_holding;
	int holding_obj;

	sf::Texture textureHolding;
	sf::Sprite spriteHolding;

	sf::Texture texture;
	sf::Sprite sprite;
	sf::Clock clock;
	sf::IntRect rectSourceSprite;

	sf::Clock clockButton;

	float movementSpeed;
	float defaultSpeed;
	float currentSpeed;
	sf::Clock bonusTimer;
	float bonusTime;

	sf::Texture speedTexture;
	sf::Sprite speedSprite;

	std::vector<ListRevenue> revenue;

	sf::SoundBuffer bufferPick;
	sf::Sound soundPick;

	void initVariable();
	void initShape();

	void initMusic();

public:
	Player(float x = 100.f, float y = 100.f);
	virtual ~Player();

	//Accesstor
	const sf::RectangleShape& getShape() const;
	const sf::Sprite& getSprite() const;
	const int& getHp() const;
	const int& getHpMax() const;

	int statusReputation;
	int statusBonus;


	//Function
	void takeDamage(const int damage);
	void gainHealth(const int health);

	void updateInput(std::vector<CraftingTable>& craftingTable, std::vector<IngredientBox>& ingredientBox, std::vector<StoreManager>& storeManager);
	void updateWindowBoundCollision(const sf::RenderTarget* target);
	void update(const sf::RenderTarget* target, std::vector<CraftingTable>& craftingTable, std::vector<IngredientBox>& ingredientBox, std::vector<StoreManager>& storeManager);
	void render(sf::RenderTarget* target);

	void updateCraftingTableCollision(std::vector<CraftingTable>& craftingTable);
	void updateIngredientBoxCollision(std::vector<IngredientBox>& ingredientBox);
	void updateStoreManagerCollision(std::vector<StoreManager>& storeManager);

	void moveHoldingSpriteTowardsPlayer(float offset, float movementSpeed);

	void callStartCrafting(std::vector<CraftingTable>& craftingTable);
	void callGetProduct(std::vector<CraftingTable>& craftingTable);

	void receiveBonus(float bonusMoveSpeed, float bonusDuration);

	int getReputation();
	int getBonus();
	void resetReputation();
	void resetBonus();
};