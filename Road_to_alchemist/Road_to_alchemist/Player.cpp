#include "Player.h"

void Player::initVariable()
{
	this->movementSpeed = 5.f;

	defaultSpeed = 5.f;
	currentSpeed = defaultSpeed + 1.f;
	bonusTime = 0.0f; // Initialize bonus time to zero


	this->hpMax = 10;
	this->hp = hpMax;

	this->is_holding = false;
	this->holding_obj = 0;

	statusReputation = 0;
}

void Player::initShape()
{
	this->texture.loadFromFile("image/bearSprites.png");
	this->sprite.setTexture(texture);
	this->rectSourceSprite = sf::IntRect(0, 0, 96, 96);
	this->sprite.setTextureRect(rectSourceSprite);

	speedTexture.loadFromFile("image/movespeed.png");
	speedSprite.setTexture(speedTexture);
	speedSprite.setScale(0.1f, 0.1f);

	//this->spriteHolding.setColor(sf::Color::Green);
	//this->shape.setSize(sf::Vector2f(50.f, 50.f));
}

void Player::initMusic()
{
	if (!bufferPick.loadFromFile("sound/pick.mp3")) {
		std::cout << "! Error::Game::Pick" << "\n";
	}

	soundPick.setBuffer(bufferPick);
	
}

Player::Player(float x, float y)
{
	this->sprite.setPosition(x, y);
	this->spriteHolding.setPosition(x, y+48.f);

	this->initVariable();
	this->initShape();
	initMusic();
}

Player::~Player()
{

}

const int& Player::getHp() const
{
	return this->hp;
}
const int& Player::getHpMax() const
{
	return this->hpMax;
}


void Player::takeDamage(const int damage)
{
	if (this->hp > 0)
	{
		this->hp -= damage;
	}
	if (this->hp < 0)
	{
		this->hp = 0;
	}
}

void Player::gainHealth(const int health)
{
	if (this->hp < this->hpMax)
		this->hp += health;

	if (this->hp > this->hpMax)
		this->hp = this->hpMax;
}
void Player::updateInput(std::vector<CraftingTable>& craftingTable, std::vector<IngredientBox>& ingredientBox, std::vector<StoreManager>& storeManager)
{
	// Keyboard input
	// Left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->sprite.move(-this->currentSpeed, 0.f);
		// Set the sprite facing left
		this->sprite.setOrigin(0.f, 0.f); 
		this->sprite.setScale(1.f, 1.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->sprite.move(this->currentSpeed, 0.f);
		// Set the sprite facing right
		this->sprite.setOrigin(96.f, 0.f);
		this->sprite.setScale(-1.f, 1.f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->sprite.move(0.f, -this->currentSpeed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		this->sprite.move(0.f, this->currentSpeed);
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::J) && this->clockButton.getElapsedTime().asSeconds() > 0.5f)
	{
		soundPick.setBuffer(bufferPick);
		soundPick.play();

		if (!this->is_holding)
		{
			this->callGetProduct(craftingTable);
			this->updateIngredientBoxCollision(ingredientBox);
			this->callStartCrafting(craftingTable);
			
		}
		else if (this->is_holding)
		{
			this->updateCraftingTableCollision(craftingTable);
			this->updateStoreManagerCollision(storeManager);
			
		}
		this->clockButton.restart();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K) && this->clockButton.getElapsedTime().asSeconds() > 0.5f)
	{
		if (this->is_holding)
		{
			this->is_holding = false;
			this->holding_obj = 0;

		}
		this->clockButton.restart();
	}
}

void Player::callStartCrafting(std::vector<CraftingTable>& craftingTable)
{
	for (size_t i = 0; i < craftingTable.size(); i++)
	{

		if (this->sprite.getGlobalBounds().intersects(craftingTable[i].getSprite().getGlobalBounds()))
		{
			switch (craftingTable[i].getType())
			{
			case CraftingTableTypes::TIER1:
				if (craftingTable[i].is_crafting == false)
				{
					craftingTable[i].startCrafting();
				}
				break;
			case CraftingTableTypes::TIER2:
				craftingTable[i].startCrafting();
				break;
			}
		}
	}
}

void Player::callGetProduct(std::vector<CraftingTable>& craftingTable)
{
	for (size_t i = 0; i < craftingTable.size(); i++)
	{

		if (this->sprite.getGlobalBounds().intersects(craftingTable[i].getSprite().getGlobalBounds()))
		{
			switch (craftingTable[i].getType())
			{
			case CraftingTableTypes::TIER1:
				if (craftingTable[i].getCombinationID() != -99)
				{
					this->is_holding = true;
					this->holding_obj = craftingTable[i].getCombinationID();
					printf("Player get Product %d\n", this->holding_obj);
					craftingTable[i].resetCombination();
				}
				break;
			case CraftingTableTypes::TIER2:
				if (craftingTable[i].getCombinationID() != -99)
				{
					this->is_holding = true;
					this->holding_obj = craftingTable[i].getCombinationID();
					printf("Player get Product %d\n", this->holding_obj);
					craftingTable[i].resetCombination();
				}
				break;
			}
		}
	}
}


void Player::updateCraftingTableCollision(std::vector<CraftingTable>& craftingTable)
{

	
	//Check the collision
	for (size_t i = 0; i < craftingTable.size(); i++)
	{
		
		if (this->sprite.getGlobalBounds().intersects(craftingTable[i].getSprite().getGlobalBounds()) &&
			craftingTable[i].isUnlock == true)
		{
			switch (craftingTable[i].getType())
			{
			case CraftingTableTypes::TIER1:
				

				// call function to update list ingredient
				if (craftingTable[i].listIngredient[0].id == -99 && craftingTable[i].is_crafting == false)
				{
						craftingTable[i].listIngredient[0].id = this->holding_obj;
						this->is_holding = false;
				}
				else if (craftingTable[i].listIngredient[1].id == -99 && craftingTable[i].is_crafting == false)
				{
						craftingTable[i].listIngredient[1].id = this->holding_obj;
						this->is_holding = false;
				}
				//printf("Player put ingredient to TIER1\n");
				break;
			case CraftingTableTypes::TIER2:

				// call function to update list ingredient
				if (craftingTable[i].listIngredient[0].id == -99 && craftingTable[i].is_crafting == false)
				{
					craftingTable[i].listIngredient[0].id = this->holding_obj;
					this->is_holding = false;
				}
				else if (craftingTable[i].listIngredient[1].id == -99 && craftingTable[i].is_crafting == false)
				{
					craftingTable[i].listIngredient[1].id = this->holding_obj;
					this->is_holding = false;
				}
				break;
			}
			//Remove the ball
			//this->swagBalls.erase(this->swagBalls.begin() + i);
			
		}
	}
	
}

void Player::updateIngredientBoxCollision(std::vector<IngredientBox>& ingredientBox)
{
	//Check the collision
	for (size_t i = 0; i < ingredientBox.size(); i++)
	{

		if (this->sprite.getGlobalBounds().intersects(ingredientBox[i].getSprite().getGlobalBounds()))
		{
			switch (ingredientBox[i].getType())
			{
			case IngredientBoxTypes::T1_1:
				this->is_holding = true;
				this->holding_obj = T1_1;
				//printf("Player pickup %d\n", this->holding_obj);
				break;
			case IngredientBoxTypes::T1_2:
				this->is_holding = true;
				this->holding_obj = T1_2;
				//printf("Player pickup %d\n", this->holding_obj);
				break;
			case IngredientBoxTypes::T1_3:
				this->is_holding = true;
				this->holding_obj = T1_3;
				//printf("Player pickup %d\n", this->holding_obj);
				break;
			case IngredientBoxTypes::T1_4:
				this->is_holding = true;
				this->holding_obj = T1_4;
				//printf("Player pickup %d\n", this->holding_obj);
				break;
			case IngredientBoxTypes::T2_1:
				this->is_holding = true;
				this->holding_obj = T2_1;
				//printf("Player pickup %d\n", this->holding_obj);
				break;
			}
		}
	}
}


void Player::updateStoreManagerCollision(std::vector<StoreManager>& storeManager)
{
	for (size_t i = 0; i < storeManager.size(); i++)
	{
		if (this->sprite.getGlobalBounds().intersects(storeManager[i].getSprite().getGlobalBounds()))
		{
			//printf("Place Order\n");
			revenue = storeManager[i].placeMenu(this->holding_obj);
			//printf("Get %d score and %d buff\n", revenue[0].score, revenue[0].bonus);
			this->is_holding = false;

			if (revenue[0].score != 0)
			{
				statusReputation = statusReputation + revenue[0].score;
			}
			if (revenue[0].bonus != 0)
			{
				statusBonus = revenue[0].bonus;
			}
		}
	}
}

void Player::updateWindowBoundCollision(const sf::RenderTarget* target)
{
	// Left
	if (this->sprite.getGlobalBounds().left <= 0.f)
		this->sprite.setPosition(0.f, this->sprite.getGlobalBounds().top);
	// Right
	if (this->sprite.getGlobalBounds().left + this->sprite.getGlobalBounds().width >= target->getSize().x)
		this->sprite.setPosition(target->getSize().x - this->sprite.getGlobalBounds().width, this->sprite.getGlobalBounds().top);

	// Top
	if (this->sprite.getGlobalBounds().top <= 55.f)
		this->sprite.setPosition(this->sprite.getGlobalBounds().left, 55.f);
	// Bottom
	if (this->sprite.getGlobalBounds().top + this->sprite.getGlobalBounds().height >= target->getSize().y -55.f)
		this->sprite.setPosition(this->sprite.getGlobalBounds().left, target->getSize().y - this->sprite.getGlobalBounds().height -55.f);
}

void Player::moveHoldingSpriteTowardsPlayer(float offset, float currentSpeed)
{
	sf::Vector2f playerPosition = this->sprite.getPosition();
	sf::Vector2f holdingPosition = this->spriteHolding.getPosition();

	/*
		// Calculate the direction vector from holdingPosition to playerPosition with offset
	sf::Vector2f direction = playerPosition - (holdingPosition + sf::Vector2f(-0.45f * this->sprite.getGlobalBounds().width, offset));

	// Calculate the distance between holdingPosition and playerPosition with offset
	float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	

	// Normalize the direction vector
	if (distance != 0)
	{
		direction /= distance;
		//printf("Distance : %f\n", distance);
	}

	// Multiply the normalized direction vector by the movement speed to control velocity
	sf::Vector2f velocity = direction * currentSpeed;

	// Update the position of spriteHolding based on the velocity
	if (distance >= 5.0f)
	{
		this->spriteHolding.move(velocity);
	}
	*/


	spriteHolding.setPosition(playerPosition.x, playerPosition.y-15.f);
	
}


void Player::receiveBonus(float bonusMoveSpeed, float bonusDuration)
{
	// Add the bonus move speed to the current speed
	currentSpeed += bonusMoveSpeed;

	// Set the bonus time and start the bonus timer
	bonusTime = bonusDuration;
	bonusTimer.restart();
}

const sf::RectangleShape& Player::getShape() const
{
	return this->shape;
}

const sf::Sprite& Player::getSprite() const
{
	return this->sprite;
}

int Player::getReputation()
{
	return statusReputation;
}

int Player::getBonus()
{
	return statusBonus;
}

void Player::resetReputation()
{
	statusReputation = 0;
}

void Player::resetBonus()
{
	statusBonus = 0;
}

void Player::update(const sf::RenderTarget* target, std::vector<CraftingTable>& craftingTable, std::vector<IngredientBox>& ingredientBox, std::vector<StoreManager>& storeManager)
{
	this->updateInput(craftingTable, ingredientBox, storeManager);

	this->moveHoldingSpriteTowardsPlayer(32.f, this->currentSpeed *0.9);

	//window bound collision
	this->updateWindowBoundCollision(target);

	if (bonusTime > 0.0f)
	{
		// Calculate the remaining bonus time
		float elapsedTime = bonusTimer.getElapsedTime().asSeconds();
		bonusTimer.restart();
		bonusTime -= elapsedTime;

		//printf("Bonus time left : %f", bonusTime);
		// Check if the bonus time has expired
		if (bonusTime <= 0.0f)
		{
			// Reset the player's speed to the default speed
			currentSpeed = defaultSpeed;

			// Ensure bonusTime does not go below zero
			bonusTime = 0.0f;
		}
	}

}

void Player::render(sf::RenderTarget* target)
{
	if (this->clock.getElapsedTime().asSeconds() > 0.5f) {
		if (this->rectSourceSprite.left == 96)
		{
			this->rectSourceSprite.left = 0;
		}
		else
		{
			this->rectSourceSprite.left += 96;
		}
		this->sprite.setTextureRect(this->rectSourceSprite);
		this->clock.restart();
	}
	if (this->is_holding)
	{
		this->spriteHolding.setColor(sf::Color::White);

		switch (this->holding_obj)
		{
		case 0:
			this->textureHolding.loadFromFile("image/T1_item_1.png");
			this->spriteHolding.setTexture(this->textureHolding);
			break;
		case 1:
			this->textureHolding.loadFromFile("image/T1_item_2.png");
			this->spriteHolding.setTexture(this->textureHolding);
			break;
		case 2:
			this->textureHolding.loadFromFile("image/T1_item_3.png");
			this->spriteHolding.setTexture(this->textureHolding);
			break;
		case 3:
			this->textureHolding.loadFromFile("image/T1_item_4.png");
			this->spriteHolding.setTexture(this->textureHolding);
			break;
		case 4:
			this->textureHolding.loadFromFile("image/T2_item_4.png");
			this->spriteHolding.setTexture(this->textureHolding);
			break;
		case 5:
			this->textureHolding.loadFromFile("image/T2_item_1.png");
			this->spriteHolding.setTexture(this->textureHolding);
			break;
		case 6:
			this->textureHolding.loadFromFile("image/T2_item_2.png");
			this->spriteHolding.setTexture(this->textureHolding);
			break;
		case 7:
			this->textureHolding.loadFromFile("image/T2_item_3.png");
			this->spriteHolding.setTexture(this->textureHolding);
			break;
		case 8:
			this->textureHolding.loadFromFile("image/potion1.png");
			this->spriteHolding.setTexture(this->textureHolding);
			break;
		case 9:
			this->textureHolding.loadFromFile("image/potion2.png");
			this->spriteHolding.setTexture(this->textureHolding);
			break;
		case 10:
			this->textureHolding.loadFromFile("image/potion3.png");
			this->spriteHolding.setTexture(this->textureHolding);
			break;
		}
	}
	else
	{
		// Hide the spriteHolding when is_holding is false
		this->spriteHolding.setColor(sf::Color(255, 255, 255, 0));
	}


	target->draw(this->sprite);
	target->draw(this->spriteHolding);
	//target->draw(this->shape);

	if (bonusTime > 0.f) {
		sf::Vector2f playerPosition = this->sprite.getPosition();
		sf::Vector2f holdingPosition = this->spriteHolding.getPosition();
		speedSprite.setPosition(playerPosition.x, playerPosition.y + 84.f);
		target->draw(speedSprite);

		// Calculate the width of the rectBar based on timeLeft and craftingTime
		float rectBarWidth = (bonusTime / 10.f) * 48.f;

		// Create a rectangle shape
		sf::RectangleShape rect;

		// Set the size of the rectangle based on rectBarWidth
		rect.setSize(sf::Vector2f(rectBarWidth, 10)); // Adjust the height as needed

		// Set the position of the rectangle
		rect.setPosition(sf::Vector2f(playerPosition.x + 24.f, playerPosition.y + 90.f)); // Adjust the Y position as needed

		// Set the fill color of the rectangle (e.g., green)
		rect.setFillColor(sf::Color::Cyan); // Adjust the color as needed

		// Draw the rectangle
		target->draw(rect);
	}

}