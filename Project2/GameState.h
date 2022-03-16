#pragma once

#include "State.h"
#include "PauseMenu.h"
#include "Tilemap.h"

class GameState : public State
{
private:
	PauseMenu* pmenu;
	Player* player;
	sf::Font font;

	Tilemap* tileMap;


	void initFonts();
	void initTextures();
	void initPauseMenu();
	void initPlayers();
	void initTileMap();

public:
	GameState(StateData* state_data);
	~GameState();

	void updateInput(const float& dt);
	void updatePlayerInput(const float& dt);
	void updatePauseMenuButtons();
	void update(const float& dt);
	void render(sf::RenderTarget& target);

};

