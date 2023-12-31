#include "StoreManager.h"

void StoreManager::initVariable()
{
	this->maxMenu = 4;
	this->nextMenuTime = (rand() % 5) + 22;
	this->elapsedTime = 18;
	penalty = 0;
}

void StoreManager::initShape(float x, float y)
{
	this->sprite.setPosition(sf::Vector2f(x,y));
}

void StoreManager::initMusic()
{
	if (!bufferCustomer.loadFromFile("sound/customer2.wav")) {
		std::cout << "! Error::Game::customer" << "\n";
	}

	soundCustomer.setBuffer(bufferCustomer);
	
}

StoreManager::StoreManager(float x, float y)
{
	this->initShape(x, y);
	this->initVariable();
	initMusic();
}

StoreManager::~StoreManager()
{

}
int StoreManager::getPenalty()
{
	return penalty;
}

void StoreManager::resetPenalty()
{
	penalty = 0;
}

void StoreManager::generateMenu(int reputation)
{
	soundCustomer.setBuffer(bufferCustomer);
	soundCustomer.play();

	// Create a default-initialized ListMenu object
	ListMenu newMenu;

	printf("gameStatus : reputation : %d", reputation);

	// Set its default parameters
	newMenu.id = rand() % 3;
	newMenu.quantity = 0;
	newMenu.bonus = (rand() % 3);
	newMenu.craftingTime = 46.0f - (reputation / 18.0f) - (newMenu.bonus * 1.0f);
	newMenu.timeLeft = newMenu.craftingTime;
	newMenu.score = 20;

	newMenu.x = 900.f + rand() % 50;
	newMenu.y = 500.f - (100.f * listMenu.size());

	newMenu.currentX = newMenu.x;
	newMenu.currentY = 0.f;
	newMenu.offsetXProduct = 100.f;
	newMenu.offsetYProduct = 25.f;

	newMenu.speed = 100.f;

	newMenu.receiveOrder = false;
	newMenu.isWait = true;

	newMenu.maxWidthBar = 50.f;

	newMenu.isHappy = false;
	newMenu.textureHappy.loadFromFile("image/smile.png");
	newMenu.spriteHappy.setTexture(newMenu.textureHappy);
	newMenu.spriteHappy.setScale(sf::Vector2f(0.04f, 0.04f));

	sf::Clock clock;
	newMenu.clock = clock;
	newMenu.rectSourceSprite = sf::IntRect(0, 96 * (newMenu.bonus + 1), 96, 96);


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

	revenueItem.bonus = 0;
	revenueItem.score = 0;

	bool isPlaced = false;
	int idx = 0;

	for (auto& i : this->listMenu)
	{
		

		if (i.id == 0 && potion == 8)
		{
			revenueItem.bonus = i.bonus;
			revenueItem.score = 20 + ((i.timeLeft / i.craftingTime) * 20);
			//listMenu.erase(listMenu.begin() + idx);
			i.receiveOrder = true;
			i.y = 720.f;

			isPlaced = true;
			printf("Success sell potion id %d order", i.id);
			break;
		}


		if (i.id == 1 && potion == 9)
		{
			revenueItem.bonus = i.bonus;
			revenueItem.score = 20 + ((i.timeLeft / i.craftingTime) * 20);
			//listMenu.erase(listMenu.begin() + idx);
			i.receiveOrder = true;
			i.y = 720.f;
			isPlaced = true;
			printf("Success sell potion id %d order", i.id);
			break;
		}


		if (i.id == 2 && potion == 10)
		{
			revenueItem.bonus = i.bonus;
			revenueItem.score = 20 + ((i.timeLeft / i.craftingTime) * 20);
			//listMenu.erase(listMenu.begin() + idx);
			i.receiveOrder = true;
			i.y = 720.f;
			isPlaced = true;
			printf("Success sell potion id %d order", i.id);
			break;
		}
		
		idx++;
	}
	revenue.push_back(revenueItem);

	if (isPlaced == true)
	{
		for (auto& i : this->listMenu)
		{
			i.isMoving = true;
		}
	}

	return revenue;
}

void StoreManager::addTimeCustomer(float time)
{
	for (auto& i : this->listMenu)
	{
		i.timeLeft += time;
		i.isHappy = true;
	}
}

const sf::Sprite& StoreManager::getSprite() const
{
	return this->sprite;
}

void StoreManager::update(int reputation)
{
	float deltaTime = this->clock.restart().asSeconds();
	this->elapsedTime += deltaTime;

	if (this->elapsedTime > (this->nextMenuTime - (reputation / 15.f)))
	{
		if (listMenu.size() < maxMenu)
		{
			printf("\n---- Generate Order ----\n");
			this->generateMenu(reputation);
			printf("------------------------\n");
		}
		this->elapsedTime = 0.f;
	}
	bool isErase = false;

	int idx = 0;
	float elaspTime = clockMenu.getElapsedTime().asSeconds();
	clockMenu.restart();
	// Update customer positions
	for (auto& i : this->listMenu)
	{
		if (i.receiveOrder)
		{
			if (i.currentY >= 600.f)
			{
				listMenu.erase(listMenu.begin() + idx);
				printf("Erase customer");
				isErase = true;
			}
		}
		else if(i.isWait == true)
		{
			i.y = 500.f - (100.f * idx);
		}

		// Error - clock update but error -> customer won't leave

		if (i.isHappy) {
			elaspTime = elaspTime * 0.8f;
		}


		i.timeLeft = i.timeLeft - elaspTime;

		if (i.timeLeft <= 0 && i.receiveOrder == false)
		{
			i.isWait = false;
			i.receiveOrder = true;
			i.isMoving = true;
			i.y = 720.f;
			penalty -= 20;
		}
		
		idx++;
	}

	if (isErase == true)
	{

		for (auto& i : this->listMenu)
		{
			i.y = 500.f - (100.f * idx);

			i.isMoving = true;
		}
	}


	for (auto& i : this->listMenu)
	{
		if (i.isMoving)
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
				i.isMoving = false;
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
}

void StoreManager::render(sf::RenderTarget& target)
{
	int idx = 0;
	for (auto& i : this->listMenu)
	{
		i.textureCustomer.loadFromFile("image/bearSprites.png");
		i.spriteCustomer.setTexture(i.textureCustomer);
		//i.rectSourceSprite = sf::IntRect(0, 96 * (i.bonus + 1), 96, 96);
		i.spriteCustomer.setTextureRect(i.rectSourceSprite);
		idx++;

		if (i.clock.getElapsedTime().asSeconds() > 0.5f) {
			//printf("shift sprite");
			if (i.rectSourceSprite.left == 96)
			{
				i.rectSourceSprite.left = 0;
			}
			else
			{
				i.rectSourceSprite.left += 96;
			}
			i.spriteCustomer.setTextureRect(i.rectSourceSprite);
			i.clock.restart();
		}

		target.draw(i.spriteCustomer);

		sf::Texture textureProduct;
		sf::Sprite spriteProduct;

		switch (i.id)
		{
		case 0:
			i.textureProduct.loadFromFile("image/potion1.png");
			i.spriteProduct.setTexture(i.textureProduct);
			i.textureBorder1.loadFromFile("image/ItemBorder.png");
			i.spriteBorder1.setTexture(i.textureBorder1);

			i.spriteProduct.setPosition(sf::Vector2f(i.currentX + i.offsetXProduct, i.currentY+i.offsetYProduct));
			i.spriteBorder1.setPosition(sf::Vector2f(i.currentX + i.offsetXProduct, i.currentY + i.offsetYProduct));
			break;
		case 1:
			i.textureProduct.loadFromFile("image/potion2.png");
			i.spriteProduct.setTexture(i.textureProduct);
			i.textureBorder1.loadFromFile("image/ItemBorder.png");
			i.spriteBorder1.setTexture(i.textureBorder1);

			i.spriteProduct.setPosition(sf::Vector2f(i.currentX + i.offsetXProduct, i.currentY + i.offsetYProduct));
			i.spriteBorder1.setPosition(sf::Vector2f(i.currentX + i.offsetXProduct, i.currentY + i.offsetYProduct));
			break;
		case 2:
			i.textureProduct.loadFromFile("image/potion3.png");
			i.spriteProduct.setTexture(i.textureProduct);
			i.textureBorder1.loadFromFile("image/ItemBorder.png");
			i.spriteBorder1.setTexture(i.textureBorder1);

			i.spriteProduct.setPosition(sf::Vector2f(i.currentX + i.offsetXProduct, i.currentY + i.offsetYProduct));
			i.spriteBorder1.setPosition(sf::Vector2f(i.currentX + i.offsetXProduct, i.currentY + i.offsetYProduct));
			break;
		default:
			break;
		}
		target.draw(i.spriteBorder1);
		target.draw(i.spriteProduct);


		// Calculate the width of the rectBar based on timeLeft and craftingTime
		float rectBarWidth = (i.timeLeft / i.craftingTime) * i.maxWidthBar;

		// Create a rectangle shape
		sf::RectangleShape rect;

		// Set the size of the rectangle based on rectBarWidth
		rect.setSize(sf::Vector2f(rectBarWidth, 10)); // Adjust the height as needed

		// Set the position of the rectangle
		rect.setPosition(sf::Vector2f(i.currentX + i.offsetXProduct, i.currentY + i.offsetYProduct - 10)); // Adjust the Y position as needed

		// Set the fill color of the rectangle (e.g., green)
		rect.setFillColor(sf::Color::Green); // Adjust the color as needed

		// Draw the rectangle
		target.draw(rect);

		if (i.isHappy) {
			//i.textureHappy.loadFromFile("image/smile.png");
			i.spriteHappy.setTexture(i.textureHappy);
			//i.spriteHappy.setScale(sf::Vector2f(0.04f, 0.04f));
			i.spriteHappy.setPosition(sf::Vector2f(i.currentX + i.offsetXProduct+32.f, i.currentY + i.offsetYProduct));
			target.draw(i.spriteHappy);
		}
	}


	this->texture.loadFromFile("image/Store.png");
	this->sprite.setTexture(this->texture);
	this->sprite.setScale(sf::Vector2f(1.5f, 1.5f));

	target.draw(this->sprite);
}