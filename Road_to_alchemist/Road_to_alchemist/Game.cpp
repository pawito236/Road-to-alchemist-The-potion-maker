#include "Game.h"

void Game::initVariable()
{
	this->endGame = false;
}

void Game::initWindow()
{
	this->texture.loadFromFile("image/map.png");
	this->sprite.setTexture(this->texture);

	this->videoMode = sf::VideoMode(1280, 720);
	this->window = new sf::RenderWindow(this->videoMode, "Game 2", sf::Style::Close | sf::Style::Titlebar);
}

//Construvtors and Destructor
Game::Game()
{

	this->initVariable();
	this->initWindow();
	this->window->setFramerateLimit(60);


	this->spawnMapItem();
}

Game::~Game()
{
	delete this->window;
}


//Function
void Game::poolEvents()
{
	while (this->window->pollEvent(sfmlEvent))
	{
		switch (this->sfmlEvent.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->sfmlEvent.key.code == sf::Keyboard::Escape)
			{
				this->window->close();
				break;
			}
		}
	}
}

void Game::spawnMapItem()
{
	this->craftingTable.push_back(CraftingTable(0, 100.f, 100.f));
	this->craftingTable.push_back(CraftingTable(1, 100.f, 300.f));

	this->ingredientBox.push_back(IngredientBox(0, 300.f, 100.f));
	this->ingredientBox.push_back(IngredientBox(1, 300.f, 200.f));
	this->ingredientBox.push_back(IngredientBox(2, 300.f, 300.f));
	this->ingredientBox.push_back(IngredientBox(3, 400.f, 100.f));
	this->ingredientBox.push_back(IngredientBox(4, 400.f, 200.f));
	this->ingredientBox.push_back(IngredientBox(5, 400.f, 300.f));

}

void Game::update()
{
	this->poolEvents();
	
	if (this->endGame == false)
	{

		this->updatePlayer();

		//this->updateCollision();
		//this->updateGui();

		for (auto& i : this->craftingTable)
		{
			i.update();
		}

		for (auto& i : this->ingredientBox)
		{
			i.update();
		}
	}
}

void Game::updatePlayer()
{
	this->player.update(this->window, this->craftingTable, this->ingredientBox);


	if (this->player.getHp() <= 0)
	{
		this->endGame = true;
	}
}



void Game::render()
{
	this->window->clear();
	this->window->draw(this->sprite);
	for (auto& i : this->craftingTable)
	{
		//i.draw(*this->window);
		i.render(*this->window);
	}

	for (auto& i : this->ingredientBox)
	{
		i.render(*this->window);
	}
	this->player.render(this->window);


	this->window->display();
}



bool Game::running()
{
	return this->window->isOpen();
}

