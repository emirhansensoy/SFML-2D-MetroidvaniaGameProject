#pragma once

#include "Gui.h"

class PauseMenu
{
private:
	//Variables
	sf::Font& font;
	sf::Text menuText;

	sf::RectangleShape background;
	sf::RectangleShape container;

	std::map <std::string, gui::Button*> buttons;


	//Private functions


public:
	//Constructors and destructors
	PauseMenu(sf::RenderWindow& window, sf::Font& font);
	~PauseMenu();

	//Accessors
	std::map <std::string, gui::Button*>& getButtons();


	//Functions
	const bool isButtonPressed(const std::string key);
	void addButtons(const std::string key, float y, const std::string text);
	void update(sf::Vector2f& mousePos);
	void render(sf::RenderTarget& target);

};

