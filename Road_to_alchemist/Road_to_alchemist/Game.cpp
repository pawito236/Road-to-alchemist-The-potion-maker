#include "Game.h"

void Game::initVariable()
{
	this->endGame = false;
	isMenu = true;
	isMenu2 = false;
	isMenu3 = false;
	reputation = 0;
}

void Game::initWindow()
{
	this->texture.loadFromFile("image/Map1.png");
	this->sprite.setTexture(this->texture);

	this->videoMode = sf::VideoMode(1280, 720);
	this->window = new sf::RenderWindow(this->videoMode, "Game 2", sf::Style::Close | sf::Style::Titlebar);
}

void Game::initFont()
{
	if (!this->font.loadFromFile("font/PixellettersFull.ttf"))
	{
		std::cout << "! Error::Game::INITFONT::COULD NOT LOAD PixellettersFull.ttf" << "\n";
	}
}

void Game::initText()
{
	//Gui text init
	this->reputationText.setFont(this->font);
	this->reputationText.setFillColor(sf::Color::White);
	this->reputationText.setCharacterSize(32);
	this->reputationText.setString("text");
}

//Construvtors and Destructor
Game::Game()
{

	this->initVariable();
	this->initWindow();
	initFont();
	initText();
	this->window->setFramerateLimit(60);


	//this->spawnMapItem();
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

				craftingTable.clear();
				ingredientBox.clear();
				storeManager.clear();

				// Create a new game window and reset game variables
				initWindow();
				initFont();
				initText();

				endGame = false;
				isMenu = true;
				isMenu2 = false;
				isMenu3 = false;
				reputation = 0;

				break;
			}
		case sf::Event::MouseMoved: // Add this case to track mouse movement
			this->mousePosition = sf::Mouse::getPosition(*this->window);
			break;
		}
	}
}

void Game::spawnMapItem()
{
	this->craftingTable.push_back(CraftingTable(1, 130.f, 380.f, 0));
	this->craftingTable.push_back(CraftingTable(0, 210.f, 235.f, 0));

	this->craftingTable.push_back(CraftingTable(1, 285.f, 380.f, 10));
	this->craftingTable.push_back(CraftingTable(0, 360.f, 235.f, 10));

	this->ingredientBox.push_back(IngredientBox(0, 300.f, 100.f)); //yellow
	this->ingredientBox.push_back(IngredientBox(1, 450.f, 100.f)); //blue
	this->ingredientBox.push_back(IngredientBox(2, 600.f, 100.f)); //red
	this->ingredientBox.push_back(IngredientBox(3, 500.f, 235.f)); //plant
	this->ingredientBox.push_back(IngredientBox(4, 500.f, 380.f)); //bottle
	//this->ingredientBox.push_back(IngredientBox(5, 400.f, 300.f));

	this->storeManager.push_back(StoreManager(690.f, 280.f));

}

void Game::update()
{
	this->poolEvents();
	
	if (isMenu == true)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
			isMenu = false;
			this->spawnMapItem();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
			isMenu2 = true;
			isMenu3 = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
			isMenu3 = true;
			isMenu2 = false;
		}
	}
	else if (this->endGame == false)
	{

		this->updatePlayer();


		//this->updateCollision();
		this->updateGui();

		for (auto& i : this->craftingTable)
		{
			i.update(reputation);
		}

		for (auto& i : this->ingredientBox)
		{
			i.update();
		}

		for (auto& i : this->storeManager)
		{
			i.update(reputation);
		}
	}
}

void Game::updatePlayer()
{
	this->player.update(this->window, this->craftingTable, this->ingredientBox, this->storeManager);


	if (this->player.getHp() <= 0)
	{
		this->endGame = true;
	}

	if (player.getReputation() != 0)
	{
		reputation = reputation + player.getReputation();
		player.resetReputation();
	}

	if (player.getBonus() != 0)
	{
		int bonus = player.getBonus();
		player.resetBonus();

		switch (bonus)
		{
		case 1:
			//player.move += 50.f;
			player.receiveBonus(2.f, 10.f);
			break;
		case 2:
			for (auto& i : this->storeManager)
			{
				i.addTimeCustomer(5.f);
			}
			break;
		default:
			break;
		}
	}
}

void Game::updateGui()
{
	std::stringstream ss;

	ss << "Reputation: " << this->reputation << "\n";
	ss << "Mouse Position: (" << this->mousePosition.x << ", " << this->mousePosition.y << ")\n";

	this->reputationText.setString(ss.str());
}

void Game::renderGui(sf::RenderTarget* target)
{
	target->draw(this->reputationText);
}

void Game::render()
{
	this->window->clear();
	this->window->draw(this->sprite);
	if (isMenu == true)
	{
		this->textureMenu.loadFromFile("image/MainMenu1.png");
		this->spriteMenu.setTexture(this->textureMenu);
		this->window->draw(this->spriteMenu);

		if (isMenu2)
		{
			this->textureMenu2.loadFromFile("image/MainMenu2.png");
			this->spriteMenu2.setTexture(this->textureMenu2);
			this->window->draw(this->spriteMenu2);
		}
		if (isMenu3)
		{
			this->textureMenu3.loadFromFile("image/MainMenu3.png");
			this->spriteMenu3.setTexture(this->textureMenu3);
			this->window->draw(this->spriteMenu3);
		}
	}
	else if (endGame == false)
	{
		for (auto& i : this->craftingTable)
		{
			//i.draw(*this->window);
			i.render(*this->window);
			i.renderGui(this->window);
		}

		for (auto& i : this->ingredientBox)
		{
			i.render(*this->window);
		}

		for (auto& i : this->storeManager)
		{
			i.render(*this->window);
		}

		this->player.render(this->window);
		renderGui(this->window);
	}

	this->window->display();
}



bool Game::running()
{
	return this->window->isOpen();
}

