#include "IngredientBox.h"


void IngredientBox::initShape(float x, float y)
{
	switch (this->type)
	{
	case T1_1:
		if (!this->texture.loadFromFile("image/ingredientBox_T1_1.png"))
		{
			printf("Error loading ingredientBox_T1_1.png");
		}
		this->sprite.setTexture(this->texture);
		break;
	case T1_2:
		if (!this->texture.loadFromFile("image/ingredientBox_T1_2.png"))
		{
			printf("Error loading ingredientBox_T1_2.png");
		}
		this->sprite.setTexture(this->texture);
		break;
	case T1_3:
		if (!this->texture.loadFromFile("image/ingredientBox_T1_3.png"))
		{
			printf("Error loading ingredientBox_T1_3.png");
		}
		this->sprite.setTexture(this->texture);
		break;
	case T1_4:
		if (!this->texture.loadFromFile("image/ingredientBox_T1_4.png"))
		{
			printf("Error loading ingredientBox_T1_4.png");
		}
		this->sprite.setTexture(this->texture);
		break;
	case T2_1:
		if (!this->texture.loadFromFile("image/ingredientBox_T2_1.png"))
		{
			printf("Error loading ingredientBox_T2_1.png");
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

	this->sprite.setScale(sf::Vector2f(1.25f, 1.25f));
}

IngredientBox::IngredientBox(int type, float x, float y)
	:type(type)
{
	//this->type = type;
	this->initShape(x, y);
}

IngredientBox::~IngredientBox()
{

}

const sf::Sprite& IngredientBox::getSprite() const
{
	return this->sprite;
}

const int& IngredientBox::getType() const
{
	return this->type;
}


void IngredientBox::update()
{

}


void IngredientBox::render(sf::RenderTarget& target)
{
	this->sprite.setTexture(this->texture);

	target.draw(this->sprite);
}

void IngredientBox::draw(sf::RenderWindow& window)
{
	window.draw(this->sprite);
}
