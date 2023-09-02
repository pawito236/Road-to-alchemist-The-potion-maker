#include "StoreManager.h"

void StoreManager::initVariable()
{
	this->maxMenu = 3;
	this->nextMenuTime = rand() % 2 + 2;
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

	newMenu.x = 900.f;
	newMenu.y = 600.f - (150.f * listMenu.size());

	newMenu.currentX = newMenu.x;
	newMenu.currentY = 0.f;

	newMenu.speed = 100.f;


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

	listMenu[listMenu.size()-1].spriteCustomer.setPosition(listMenu[listMenu.size()-1].currentX, listMenu[listMenu.size()-1].currentY);

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

	int idx = 0;
	// Update customer positions
	for (auto& i : this->listMenu)
	{
		i.y = 600.f - (150.f * idx);
		idx++;
	}

	for (auto& i : this->listMenu)
	{
		// Calculate the direction vector from current position to target position
		sf::Vector2f direction(i.x - i.currentX, i.y - i.currentY);

		// Calculate the distance to move in this frame based on speed and deltaTime
		float distanceToMove = i.speed * deltaTime;
		//printf("distance %f, %f by %f", direction.x, direction.y, distanceToMove);

		// If the distance remaining to the target is less than distanceToMove,
		// set the position to the target directly; otherwise, move by distanceToMove.
		if (direction.x * direction.x + direction.y * direction.y < distanceToMove * distanceToMove)
		{
			i.currentX = i.x;
			i.currentY = i.y;
		}
		else
		{
			direction = direction / std::sqrt(direction.x * direction.x + direction.y * direction.y);
			i.currentX += direction.x * distanceToMove;
			i.currentY += direction.y * distanceToMove;
		}

		//printf("Position x: %f, y: %f\n-------------\n", i.currentX, i.currentY);

		i.spriteCustomer.setPosition(i.currentX, i.currentY);
	}
}

void StoreManager::render(sf::RenderTarget& target)
{
	int idx = 0;
	for (auto& i : this->listMenu)
	{
		i.textureCustomer.loadFromFile("image/bearSprites.png");
		i.spriteCustomer.setTexture(i.textureCustomer);
		i.rectSourceSprite = sf::IntRect(0, 0, 96, 96);
		i.spriteCustomer.setTextureRect(i.rectSourceSprite);
		idx++;

		target.draw(i.spriteCustomer);
	}


	this->texture.loadFromFile("image/Store.png");
	this->sprite.setTexture(this->texture);
	this->sprite.setScale(sf::Vector2f(1.5f, 1.5f));

	target.draw(this->sprite);
}