#pragma once

#include "MainMenuState.h"

class Game
{
private:
	//Variables
	GraphicsSettings gfxSettings;
	StateData stateData;
	sf::RenderWindow *window;
	sf::Event ev;

	float gridSize;

	//States
	std::stack<State*> states;

	//dt
	sf::Clock dtClock;
	float dt;

	//Private functions
	void initVariables();
	void initGraphicsSettings();
	void initWindow();
	void initStateData();
	void initStates();

public:
	//Constructors and destructors
	Game();
	~Game();

	//Accessors

	//Regular

	//Functions
	void run();
	void updateDt();
	void pollEvents();
	void update();
	void render();
};

