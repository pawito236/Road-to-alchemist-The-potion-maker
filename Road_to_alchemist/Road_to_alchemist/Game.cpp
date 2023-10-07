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
	this->texture.loadFromFile("image/Map2.png");
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

	this->playerName.setFont(this->font);
	this->playerName.setFillColor(sf::Color::White);
	this->playerName.setCharacterSize(40);
	this->playerName.setString("");
	playerName.setPosition(250.f, 250.f);

	leaderboardText.setFont(font);
	leaderboardText.setFillColor(sf::Color::Black);
	leaderboardText.setCharacterSize(40);
	leaderboardText.setPosition(250.f, 250.f);
}

void Game::initMusic()
{
	if (!backgroundMusic.openFromFile("sound/lofi1.ogg")) {
		// Handle the error if loading the music fails
		std::cout << "! Error::Game::backgroundMusic" << "\n";
	}
	// Set the music to loop continuously
	backgroundMusic.setLoop(true);

	// Play the background music
	backgroundMusic.play();


	if (!bufferCoin.loadFromFile("sound/coin.wav")) {
		std::cout << "! Error::Game::bufferCoin" << "\n";
	}

	soundCoin.setBuffer(bufferCoin);
	soundCoin.play();

}

//Construvtors and Destructor
Game::Game()
{

	this->initVariable();
	this->initWindow();
	initFont();
	initText();
	initMusic();
	this->window->setFramerateLimit(30);


	//this->spawnMapItem();
}

Game::~Game()
{
	delete this->window;
}


//Function
void Game::poolEvents()
{
	// https://gamedev.net/forums/topic/633951-using-sfml20-to-input-a-name/4997764/

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

				sf::Sound sound;
				sound.setBuffer(bufferCoin);
				sound.play();

				inputBuffer = "";

				/*
				saveData();
				restartGame();
				*/

				if (isMenu == false)
				{
					endGame = true;
				}
				
				break;
			}
			else if (this->sfmlEvent.key.code == sf::Keyboard::Enter && endGame == true)
			{
				//std::string playerName = input.toAnsiString();
				//printf("Player Name: %s\n", playerName.getString());
				inputBuffer = "";
				break;
			}
			break;
		case sf::Event::TextEntered:
			if (endGame == true)
			{
				if (sfmlEvent.text.unicode < 128)
				{
					if (sfmlEvent.text.unicode == 13)
					{
						inputBuffer = "";

						saveData();
						restartGame();
					}
					else
					{
						printf("unicode : %d", sfmlEvent.text.unicode);
						inputBuffer += static_cast<char>(sfmlEvent.text.unicode);
						printf("\nName : %s\n", inputBuffer.c_str());
						playerName.setString(inputBuffer.c_str());
						playerNameBuffer = inputBuffer;
					}

				}
			}
			break;
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

std::string Game::getPlayerName()
{
	sf::String input;
	sf::Text text;
	sf::Font font;

	// Load a font for displaying text input
	if (!font.loadFromFile("font/PixellettersFull.ttf")) {
		std::cerr << "Error: Could not load font." << std::endl;
		return "";
	}

	text.setFont(font);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::White);

	while (this->window->isOpen()) {
		sf::Event event;
		while (this->window->pollEvent(event)) {
			if (event.type == sf::Event::TextEntered) {
				if (event.text.unicode == '\b' && !input.isEmpty()) {
					// Handle backspace
					input.erase(input.getSize() - 1, 1);
				}
				else if (event.text.unicode < 128) {
					// Handle regular text input
					input += event.text.unicode;
				}
			}
			else if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Enter) {
					// Player pressed Enter, so return the captured name
					return input.toAnsiString();
				}
			}
			else if (event.type == sf::Event::Closed) {
				// Handle window close event
				this->window->close();
				return "";
			}
		}

		// Display the input text
		text.setString(input);
		this->window->clear();
		this->window->draw(text);
		this->window->display();
	}

	return "";
}

void Game::update()
{
	this->poolEvents();
	
	if (isMenu == true)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
			isMenu = false;
			this->spawnMapItem();

			soundCoin.setBuffer(bufferCoin);
			soundCoin.play();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
			isMenu2 = true;
			isMenu3 = false;

			soundCoin.setBuffer(bufferCoin);
			soundCoin.play();

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
			isMenu3 = true;
			isMenu2 = false;

			soundCoin.setBuffer(bufferCoin);
			soundCoin.play();

			DisplyLeaderBoard();
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

			reputation = reputation + i.getPenalty();
			i.resetPenalty();
		}
		if (reputation >= 30)
		{
			printf("\nYou Been promoted to alchemist !!!\n");
			endGame = true;
		}
	}
	else if (endGame == true)
	{
		// do sth
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
		soundCoin.setBuffer(bufferCoin);
		soundCoin.play();

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

bool Game::compareByReputation(const PlayerData& a, const PlayerData& b) {
	return a.reputation > b.reputation;
}

void Game::DisplyLeaderBoard()
{
	std::vector<PlayerData> playersList;

	// Read data from the file
	std::ifstream inputFile("player_data.txt");
	if (!inputFile.is_open()) {
		std::cerr << "Error: Could not open player_data.txt" << std::endl;
	}

	std::string line;
	while (std::getline(inputFile, line)) {
		PlayerData playerData;
		std::istringstream iss(line);
		iss >> playerData.name >> playerData.reputation;
		playersList.push_back(playerData);
	}

	inputFile.close();

	// Sort the data by reputation in descending order
	//std::sort(playersList.begin(), playersList.end(), compareByReputation);

	std::sort(playersList.begin(), playersList.end(), [](const PlayerData& a, const PlayerData& b) {
		return a.reputation > b.reputation;
	});

	// Print the sorted data
	std::cout << "Players sorted by reputation:" << std::endl;
	for (const PlayerData& playerData : playersList) {
		std::cout << "Name: " << playerData.name << ", Reputation: " << playerData.reputation << std::endl;
	}

	// Prepare the leaderboard text
	std::string leaderboardTextStr = "";

	int i = 0;

	for (const PlayerData& playerData : playersList) {
		leaderboardTextStr += "Name: " + playerData.name + ", Reputation: " + std::to_string(playerData.reputation) + "\n";
		i++;
		if (i == 5)
		{
			i = 0;
			break;
		}
	}

	leaderboardText.setString(leaderboardTextStr);
}

void Game::saveData()
{
	FILE* file = fopen("player_data.txt", "a");

	if (file == NULL) {
		printf("File open error");
	}
	else
	{
		fprintf(file, "%s %d\n", playerNameBuffer.c_str(), reputation);
		//fprintf(file, "%s %d\n", "anonymous", reputation);

		fclose(file);

		printf("save successful player_data.txt\n");
	}
}
void Game::inputPlayerName()
{

}


void Game::restartGame()
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
			this->textureMenu2.loadFromFile("image/MainMenu2-2.png");
			this->spriteMenu2.setTexture(this->textureMenu2);
			this->window->draw(this->spriteMenu2);
		}
		if (isMenu3)
		{
			this->textureMenu3.loadFromFile("image/MainMenu3.png");
			this->spriteMenu3.setTexture(this->textureMenu3);
			this->window->draw(this->spriteMenu3);

			this->window->draw(leaderboardText);
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
	else if (endGame == true)
	{
		this->textureMenu4.loadFromFile("image/MainMenu-end.png");
		this->spriteMenu4.setTexture(this->textureMenu4);
		this->window->draw(this->spriteMenu4);

		this->window->draw(playerName);
	}

	this->window->display();
}



bool Game::running()
{
	return this->window->isOpen();
}

