#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

enum IngredientBoxTypes { T1_1 = 0, T1_2, T1_3, T1_4, T2_1, T2_2, T2_3};

class IngredientBox
{
private:
	sf::CircleShape shape;
	int type;

	sf::Texture texture;
	sf::Sprite sprite;
	sf::Clock clock;
	sf::IntRect rectSourceSprite;

	void initShape(float x, float y);

public:
	IngredientBox(int type, float x, float y);
	~IngredientBox();

	//Acesstor
	const int& getType() const;
	const sf::Sprite& getSprite() const;

	void update();
	void render(sf::RenderTarget& target);

	void draw(sf::RenderWindow& window);
};

