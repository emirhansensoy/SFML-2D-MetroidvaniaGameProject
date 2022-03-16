#pragma once

#include "Gui.h"
#include "GameState.h"
#include "EditorState.h"
#include "SettingsState.h"

class MainMenuState : public State
{
private:
	//Variables
	sf::RectangleShape background;
	sf::Texture bgTex;
	sf::Font font;

	std::map <std::string, gui::Button*> buttons;


	//Private functions
	void initVariables();
	void initBackground();
	void initFonts();
	void initButtons();

public:
	//Constructors and destructors
	MainMenuState(StateData* state_data);
	~MainMenuState();


	//Functions
	void updateButtons();
	void updateInput(const float& dt);
	void update(const float& dt);

	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);

};

