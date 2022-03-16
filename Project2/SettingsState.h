#pragma once

#include "State.h"
#include "Gui.h"


class SettingsState : public State
{
private:
	//Variables
	sf::RectangleShape background;
	sf::Texture bgTex;
	sf::Font font;

	std::map <std::string, gui::Button*> buttons;
	std::map <std::string, gui::Slider*> sliders;

	sf::Text settingsText;

	std::vector<sf::VideoMode> modes;
	std::vector<std::string> fullscreenSettings;
	std::vector<std::string> framerateLimitSettings;
	std::vector<std::string> vsyncSettings;
	std::vector<std::string> antiAliasingSettings;

	//Private functions
	void initVariables();
	void initBackground();
	void initFonts();
	void initGui();
	void initText();

public:
	//Constructors and destructors
	SettingsState(StateData* state_data);
	~SettingsState();


	//Functions
	void updateGui(const float& dt);
	void updateInput(const float& dt);
	void update(const float& dt);

	void renderGui(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);

};

