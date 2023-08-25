#include "CraftingTable.h"

void CraftingTable::initShape(float x, float y)
{
	this->rectBar = sf::IntRect(28, 0, this->maxWidthBar, 28);

	this->is_crafting = false;

	switch (this->type)
	{
	case TIER1:

		if (!this->texture.loadFromFile("image/Cauldron.png"))
		{
			printf("Error loading cauldron.png");
			// Handle the error, return, or show a placeholder image.
		}
		texture.loadFromFile("image/Cauldron.png");
		this->sprite.setTexture(this->texture);
		//dthis->shape.setTexture(&this->texture);
		this->rectSourceSprite = sf::IntRect(0, 0, 64, 64);
		this->sprite.setTextureRect(rectSourceSprite);
		//this->sprite.setColor(sf::Color::Green);
		break;
	case TIER2:
		if (!this->texture.loadFromFile("image/brew_table.png"))
		{
			printf("Error loading brew_table.png");
			// Handle the error, return, or show a placeholder image.
		}
		this->sprite.setTexture(this->texture);
		break;
	}

	this->sprite.setPosition(
		sf::Vector2f(
			x,
			y
		)
	);

	this->spriteItem1.setPosition(
		sf::Vector2f(
			x,
			y-32.f
		)
	);

	this->spriteItem2.setPosition(
		sf::Vector2f(
			x+32.f,
			y-32.f
		)
	);

	this->spriteProduct.setPosition(
		sf::Vector2f(
			x + 16.f,
			y - 32.f
		)
	);

	this->spriteProductBorder.setPosition(
		sf::Vector2f(
			x + 16.f,
			y - 32.f
		)
	);

	this->spriteBorder1.setPosition(
		sf::Vector2f(
			x,
			y - 32.f
		)
	);
	this->spriteBorder2.setPosition(
		sf::Vector2f(
			x + 32.f,
			y - 32.f
		)
	);

	this->spriteBar.setPosition(
		sf::Vector2f(
			x - 32.f + 28.f,
			y - 32.f
		)
	);
	this->spriteBarBG.setPosition(
		sf::Vector2f(
			x - 32.f,
			y - 32.f
		)
	);

}

void CraftingTable::initVariable()
{
	this->combination_id = -99;
	this->combinationStatus = false;
	this->maxWidthBar = 94;
	this->craftingTime = 5.0f;
}

CraftingTable::CraftingTable(int type, float x, float y)
	:type(type)
{
	//this->type = type;
	this->initShape(x, y);
	this->initVariable();

	printf("init crafttime : %f", this->craftingTime);
}

CraftingTable::~CraftingTable()
{

}

const sf::Sprite& CraftingTable::getSprite() const
{
	return this->sprite;
}

const int& CraftingTable::getType() const
{
	return this->type;
}

void CraftingTable::update()
{
	if (this->is_crafting == true)
	{
		float deltaTime = clockcraftingTime.restart().asSeconds();
		elapsedTime += deltaTime;

		printf("elapsedTime %f", elapsedTime);

		if (elapsedTime > 5.0f)
		{
			printf("Finish Timer Craft");
			this->combinationStatus = false;
			this->is_crafting = false;
			this->elapsedTime = 0.0f;
			this->combination_id = this->temp_combination_id;
		}
	}
}
void CraftingTable::resetCombination()
{
	this->temp_combination_id = -99;
	this->combination_id = -99;
}

void CraftingTable::startCrafting()
{
	this->checkCombination();

	if (this->combinationStatus == true)
	{
		this->is_crafting = true;
		this->clockcraftingTime.restart();
	}
	
}

void CraftingTable::checkCombination()
{
	int len = sizeof(this->listIngredient) / sizeof(this->listIngredient[0]);

	switch (this->type)
	{
	case TIER1:

		if (this->listIngredient[0].id == 0 and this->listIngredient[1].id == 3 || this->listIngredient[0].id == 3 and this->listIngredient[1].id == 0) {
			this->combinationStatus = true;
			this->temp_combination_id = 5;
			printf("Start Crafting Potion 1\n");
		}
		else if (this->listIngredient[0].id == 1 and this->listIngredient[1].id == 3 || this->listIngredient[0].id == 3 and this->listIngredient[1].id == 1) {
			this->combinationStatus = true;
			this->temp_combination_id = 6;
			printf("Start Crafting Potion 2\n");
		}
		else if (this->listIngredient[0].id == 2 and this->listIngredient[1].id == 3 || this->listIngredient[0].id == 3 and this->listIngredient[1].id == 2) {
			this->combinationStatus = true;
			this->temp_combination_id = 7;
			printf("Start Crafting Potion 3\n");
		}
		else
		{
			this->combinationStatus = false;
			this->combination_id = -99;
		}
		break;
	case TIER2:

		if (this->listIngredient[0].id == 5 and this->listIngredient[1].id == 4 || this->listIngredient[0].id == 4 and this->listIngredient[1].id == 5) {
			this->combinationStatus = true;
			this->temp_combination_id = 8;
			printf("Start Crafting Potion 1\n");
		}
		else if (this->listIngredient[0].id == 6 and this->listIngredient[1].id == 4 || this->listIngredient[0].id == 4 and this->listIngredient[1].id == 6) {
			this->combinationStatus = true;
			this->temp_combination_id = 9;
			printf("Start Crafting Potion 2\n");
		}
		else if (this->listIngredient[0].id == 7 and this->listIngredient[1].id == 4 || this->listIngredient[0].id == 4 and this->listIngredient[1].id == 7) {
			this->combinationStatus = true;
			this->temp_combination_id = 10;
			printf("Start Crafting Potion 3\n");
		}
		else
		{
			this->combinationStatus = false;
			this->combination_id = -99;
		}
		break;
	}

	if (this->listIngredient[0].id != -99 and this->listIngredient[1].id != -99) {
		// Call reset list ingredient function
		this->listIngredient[0].id = -99;
		this->listIngredient[1].id = -99;
		printf("Reset Crafting Table\n");
	}
}

int CraftingTable::getCombinationID()
{
	return this->combination_id;
}

void CraftingTable::render(sf::RenderTarget& target)
{
	this->spriteItem1.setColor(sf::Color::White);
	switch (this->listIngredient[0].id)
	{
	case 0:
		this->textureItem1.loadFromFile("image/T1_item_1.png");
		this->spriteItem1.setTexture(this->textureItem1);
		break;
	case 1:
		this->textureItem1.loadFromFile("image/T1_item_2.png");
		this->spriteItem1.setTexture(this->textureItem1);
		break;
	case 2:
		this->textureItem1.loadFromFile("image/T1_item_3.png");
		this->spriteItem1.setTexture(this->textureItem1);
		break;
	case 3:
		this->textureItem1.loadFromFile("image/T1_item_4.png");
		this->spriteItem1.setTexture(this->textureItem1);
		break;
	case 4:
		this->textureItem1.loadFromFile("image/T2_item_4.png");
		this->spriteItem1.setTexture(this->textureItem1);
		break;
	case 5:
		this->textureItem1.loadFromFile("image/T2_item_1.png");
		this->spriteItem1.setTexture(this->textureItem1);
		break;
	case 6:
		this->textureItem1.loadFromFile("image/T2_item_2.png");
		this->spriteItem1.setTexture(this->textureItem1);
		break;
	case 7:
		this->textureItem1.loadFromFile("image/T2_item_3.png");
		this->spriteItem1.setTexture(this->textureItem1);
		break;
	default:
		this->spriteItem1.setColor(sf::Color(255, 255, 255, 0));
		break;
	}

	this->spriteItem2.setColor(sf::Color::White);
	switch (this->listIngredient[1].id)
	{
	case 0:
		this->textureItem2.loadFromFile("image/T1_item_1.png");
		this->spriteItem2.setTexture(this->textureItem2);
		break;
	case 1:
		this->textureItem2.loadFromFile("image/T1_item_2.png");
		this->spriteItem2.setTexture(this->textureItem2);
		break;
	case 2:
		this->textureItem2.loadFromFile("image/T1_item_3.png");
		this->spriteItem2.setTexture(this->textureItem2);
		break;
	case 3:
		this->textureItem2.loadFromFile("image/T1_item_4.png");
		this->spriteItem2.setTexture(this->textureItem2);
		break;
	case 4:
		this->textureItem2.loadFromFile("image/T2_item_4.png");
		this->spriteItem2.setTexture(this->textureItem2);
		break;
	case 5:
		this->textureItem2.loadFromFile("image/T2_item_1.png");
		this->spriteItem2.setTexture(this->textureItem2);
		break;
	case 6:
		this->textureItem2.loadFromFile("image/T2_item_2.png");
		this->spriteItem2.setTexture(this->textureItem2);
		break;
	case 7:
		this->textureItem2.loadFromFile("image/T2_item_3.png");
		this->spriteItem2.setTexture(this->textureItem2);
		break;
	default:
		this->spriteItem2.setColor(sf::Color(255, 255, 255, 0));
		break;
	}

	this->textureProductBorder.loadFromFile("image/ItemBorder.png");
	this->spriteProductBorder.setTexture(this->textureProductBorder);
	this->spriteProductBorder.setColor(sf::Color::White);
	this->spriteProduct.setColor(sf::Color::White);
	switch (this->combination_id)
	{
	case 5:
		this->textureProduct.loadFromFile("image/T2_item_1.png");
		this->spriteProduct.setTexture(this->textureProduct);

		this->spriteBorder1.setColor(sf::Color(255, 255, 255, 0));
		this->spriteBorder2.setColor(sf::Color(255, 255, 255, 0));
		break;
	case 6:
		this->textureProduct.loadFromFile("image/T2_item_2.png");
		this->spriteProduct.setTexture(this->textureProduct);

		this->spriteBorder1.setColor(sf::Color(255, 255, 255, 0));
		this->spriteBorder2.setColor(sf::Color(255, 255, 255, 0));
		break;
	case 7:
		this->textureProduct.loadFromFile("image/T2_item_3.png");
		this->spriteProduct.setTexture(this->textureProduct);

		this->spriteBorder1.setColor(sf::Color(255, 255, 255, 0));
		this->spriteBorder2.setColor(sf::Color(255, 255, 255, 0));
		break;
	case 8:
		this->textureProduct.loadFromFile("image/potion1.png");
		this->spriteProduct.setTexture(this->textureProduct);

		this->spriteBorder1.setColor(sf::Color(255, 255, 255, 0));
		this->spriteBorder2.setColor(sf::Color(255, 255, 255, 0));
		break;
	case 9:
		this->textureProduct.loadFromFile("image/potion2.png");
		this->spriteProduct.setTexture(this->textureProduct);

		this->spriteBorder1.setColor(sf::Color(255, 255, 255, 0));
		this->spriteBorder2.setColor(sf::Color(255, 255, 255, 0));
		break;
	case 10:
		this->textureProduct.loadFromFile("image/potion3.png");
		this->spriteProduct.setTexture(this->textureProduct);

		this->spriteBorder1.setColor(sf::Color(255, 255, 255, 0));
		this->spriteBorder2.setColor(sf::Color(255, 255, 255, 0));
		break;
	default:
		this->spriteProduct.setColor(sf::Color(255, 255, 255, 0));
		this->spriteProductBorder.setColor(sf::Color(255, 255, 255, 0));

		this->spriteBorder1.setColor(sf::Color::White);
		this->spriteBorder2.setColor(sf::Color::White);
		break;
	}

	switch (this->type)
	{
	case TIER1:
		if (this->clock.getElapsedTime().asSeconds() > 1.0f) {

			if (this->rectSourceSprite.left == 192)
			{
				rectSourceSprite.left = 0;
			}
			else
			{
				this->rectSourceSprite.left += 64;
			}
			this->sprite.setTextureRect(this->rectSourceSprite);
			this->clock.restart();
		}

		this->sprite.setTextureRect(this->rectSourceSprite);
		break;
	case TIER2:
		break;
	}

	if (this->is_crafting == true)
	{
		this->spriteBorder1.setColor(sf::Color(255, 255, 255, 0));
		this->spriteBorder2.setColor(sf::Color(255, 255, 255, 0));

		this->spriteBarBG.setColor(sf::Color::White);
		this->spriteBar.setColor(sf::Color::White);

		this->textureBarBG.loadFromFile("image/barBG.png");
		this->spriteBarBG.setTexture(this->textureBarBG);
		this->textureBar.loadFromFile("image/bar.png");
		this->spriteBar.setTexture(this->textureBar);

		// Calculate the percentage of elapsedTime relative to craftingTime
		float percentageComplete = this->elapsedTime / this->craftingTime;
		printf("this->elapsedTime / this->craftingTime : %f / %f\n", this->elapsedTime, this->craftingTime);
		printf("percentageComplete : %f\n", percentageComplete);

		// Ensure that the percentage is clamped between 0 and 1
		percentageComplete = std::min(std::max(percentageComplete, 0.f), 1.f);

		// Set the rectBar width based on the percentage
		this->rectBar.width = static_cast<int>(percentageComplete * this->maxWidthBar);
		printf("rectBar.width : %d\n", rectBar.width);

		this->spriteBar.setTextureRect(this->rectBar);

	}
	else
	{
		this->spriteBarBG.setColor(sf::Color(255, 255, 255, 0));
		this->spriteBar.setColor(sf::Color(255, 255, 255, 0));
	}

	this->sprite.setTexture(this->texture);

	this->textureBorder1.loadFromFile("image/ItemBorder.png");
	this->textureBorder2.loadFromFile("image/ItemBorder.png");
	this->spriteBorder1.setTexture(this->textureBorder1);
	this->spriteBorder2.setTexture(this->textureBorder2);

	target.draw(this->sprite);
	target.draw(this->shape);
	target.draw(this->spriteBorder1);
	target.draw(this->spriteBorder2);
	target.draw(this->spriteItem1);
	target.draw(this->spriteItem2);
	target.draw(this->spriteProductBorder);
	target.draw(this->spriteProduct);
	
	target.draw(this->spriteBarBG);
	target.draw(this->spriteBar);
}

void CraftingTable::draw(sf::RenderWindow& window)
{
	//window.draw(this->sprite);
	window.draw(this->shape);
}