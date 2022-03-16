#pragma once

#include "Player.h"
#include "GraphicsSettings.h"

class StateData;
class Player;
class GraphicsSettings;

class State
{
protected:
	StateData* stateData;
	sf::RenderWindow* window{};
	std::map<std::string, sf::Texture> textures;

	bool quit;
	bool paused;

	float keyTime;
	float keyTimeMax;
	float gridSize;

	std::stack <State*>* states;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	sf::Vector2u mousePosGrid;
	

public:
	State(StateData* state_data);
	virtual ~State();

	//Accessors
	const bool& getQuit() const;
	const bool getKeyTime();

	//Functions
	void endState();
	void pauseState();
	void unpauseState();

	virtual void updateKeyTime(const float& dt);
	virtual void updateMousePos();
	virtual void updateInput(const float& dt) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget& target) = 0;
};

class StateData
{
public:
	//Variables
	float gridSize{};
	GraphicsSettings* gfxSettings{};
	sf::RenderWindow* window{};
	std::stack <State*>* states{};

	StateData() {}
};