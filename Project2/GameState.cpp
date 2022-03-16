#include "stdafx.h"
#include "GameState.h"

//Private functions
void GameState::initFonts()
{
	if (!font.loadFromFile("Fonts/slkscr.ttf"))
	{
		std::cout << "ERROR::GAMESTATE::COULD NOT LOAD FONT" << std::endl;
	}

}

void GameState::initTextures()
{
	sf::Texture temp;

	if (!this->textures["PLAYER_SHEET"].loadFromFile("Images/playerSheet.png"))
	{
		std::cout << "ERROR::GAME_STATE::COULD NOT LOAD PLAYER TEXTURE" << std::endl;
	}
}

void GameState::initPauseMenu()
{
	this->pmenu = new PauseMenu(*this->window, this->font);
	this->pmenu->addButtons("QUIT", 920.f, "Quit");
}

void GameState::initPlayers()
{
	this->player = new Player(400, 400, this->textures["PLAYER_SHEET"]);
}

void GameState::initTileMap()
{
	this->tileMap = new Tilemap(this->stateData->gridSize, 10, 10);
}

//Constructors and destructors
GameState::GameState(StateData* state_data) : State(state_data)
{
	this->initFonts();
	this->initTextures();
	this->initPauseMenu();
	this->initPlayers();
	this->initTileMap();
}

GameState::~GameState()
{
	delete this->pmenu;
	delete this->player;
	delete this->tileMap;
}

//Functions
void GameState::updateInput(const float& dt)
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && this->getKeyTime())
	{
		if (!this->paused)
		{
			this->pauseState();
		}
		else
		{
			this->unpauseState();
		}
	}
}

void GameState::updatePlayerInput(const float& dt)
{
	//Update player input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->player->move(0.f, -1.f, dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->player->move(-1.f, 0.f, dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->player->move(1.f, 0.f, dt);
	}
}

void GameState::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonPressed("QUIT"))
	{
		this->endState();
	}
}

void GameState::update(const float& dt)
{
	this->updateMousePos();
	this->updateKeyTime(dt);
	this->updateInput(dt);
	
	if (!this->paused)
	{
		this->updatePlayerInput(dt);
		this->player->update(dt);
	}
	else//Paused update
	{
		this->pmenu->update(this->mousePosView);
		this->updatePauseMenuButtons();
	}
	
}

void GameState::render(sf::RenderTarget& target)
{
	//this->map.render(target);

	this->player->render(target);

	if (this->paused) //Pause menu render
	{
		this->pmenu->render(target);
	}
	
}
