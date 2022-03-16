#pragma once

#include "State.h"
#include "PauseMenu.h"
#include "Gui.h"
#include "Tilemap.h"

class State;
class PauseMenu;
class Gui;
class Tilemap;


class EditorState : public State
{
private:
	PauseMenu* pmenu;
	sf::Font font;

	std::map <std::string, gui::Button*> buttons;

	Tilemap* tileMap;

	sf::RectangleShape selectorRect;

	void initVariables();
	void initFonts();
	void initPauseMenu();
	void initButtons();
	void initGui();
	void initTilemap();

public:
	EditorState(StateData* state_data);
	~EditorState();

	void updateButtons();
	void updatePauseMenuButtons();
	void updateGui();
	void updateInput(const float& dt);
	void updateEditorInput(const float& dt);
	void update(const float& dt);

	void renderButtons(sf::RenderTarget& target);
	void renderGui(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);

};

