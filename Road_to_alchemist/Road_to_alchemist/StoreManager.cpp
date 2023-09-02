#include "StoreManager.h"

void StoreManager::initVariable()
{
	this->maxMenu = 3;
	this->nextMenuTime = rand() % 5 + 5;
}

void StoreManager::initShape(float x, float y)
{
	this->sprite.setPosition(sf::Vector2f(x,y));
}

StoreManager::StoreManager(float x, float y)
{
	this->initShape(x, y);
	this->initVariable();
}

StoreManager::~StoreManager()
{

}

void StoreManager::generateMenu()
{
	// Create a default-initialized ListMenu object
	ListMenu newMenu;

	// Set its default parameters
	newMenu.id = rand() % 3;
	newMenu.quantity = 0;
	newMenu.craftingTime = 0.0f;
	newMenu.timeLeft = 0.0f;
	newMenu.bonus = 0;
	newMenu.score = 10;

	newMenu.x = 0;
	newMenu.y = 0;

	// Set other properties as needed based on your requirements

	// After configuring the ListMenu object, add it to the vector
	listMenu.push_back(newMenu);

	//int indexToRemove = 2;

	//if (indexToRemove >= 0 && indexToRemove < listMenu.size()) {
		// Use erase to remove the item at the specified index
	//	listMenu.erase(listMenu.begin() + indexToRemove);
	//}

	for (auto& i : this->listMenu)
	{
		printf("\nId %d\n", i.id);
	}

}
std::vector<ListRevenue> StoreManager::placeMenu(int potion)
{
	std::vector<ListRevenue> revenue;

	ListRevenue revenueItem;

	revenueItem.bonus = -99;
	revenueItem.score = -99;

	int idx = 0;

	for (auto& i : this->listMenu)
	{

		if (i.id == 0 && potion == 8)
		{
			revenueItem.bonus = -99;
			revenueItem.score = 10;
			listMenu.erase(listMenu.begin() + idx);

			printf("Success sell potion id %d order", i.id);
			break;
		}


		if (i.id == 1 && potion == 9)
		{
			revenueItem.bonus = -99;
			revenueItem.score = 15;
			listMenu.erase(listMenu.begin() + idx);
			printf("Success sell potion id %d order", i.id);
			break;
		}


		if (i.id == 2 && potion == 10)
		{
			revenueItem.bonus = -99;
			revenueItem.score = 30;
			listMenu.erase(listMenu.begin() + idx);
			printf("Success sell potion id %d order", i.id);
			break;
		}
		
		idx++;
	}
	revenue.push_back(revenueItem);

	return revenue;
}

const sf::Sprite& StoreManager::getSprite() const
{
	return this->sprite;
}

void StoreManager::update()
{
	float deltaTime = this->clock.restart().asSeconds();
	this->elapsedTime += deltaTime;

	if (this->elapsedTime > this->nextMenuTime)
	{
		if (listMenu.size() < maxMenu)
		{
			printf("\n---- Generate Order ----\n");
			this->generateMenu();
			printf("------------------------\n");
		}
		this->elapsedTime = 0.f;
	}
}

void StoreManager::render(sf::RenderTarget& target)
{
	this->texture.loadFromFile("image/Store.png");
	this->sprite.setTexture(this->texture);
	this->sprite.setScale(sf::Vector2f(1.5f, 1.5f));

	target.draw(this->sprite);
}