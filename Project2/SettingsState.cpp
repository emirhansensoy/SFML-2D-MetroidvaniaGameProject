#include "stdafx.h"
#include "SettingsState.h"

//Private functions
void SettingsState::initVariables()
{
	this->modes = sf::VideoMode::getFullscreenModes();
	this->fullscreenSettings = { "On", "Off" };
	this->framerateLimitSettings = { "None", "30", "60", "75", "120", "144", "240" };
	this->vsyncSettings = { "On", "Off" };
	this->antiAliasingSettings = { "None", "2x", "4x", "8x" };
}

void SettingsState::initBackground()
{
	this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));

	if (!this->bgTex.loadFromFile("Images/backgroundTexture.png"))
	{
		std::cout << "ERROR::SETTINGSSTATE::COULD NOT LOAD BG_TEX" << std::endl;
	}

	this->background.setTexture(&this->bgTex);
}

void SettingsState::initFonts()
{
	if (!font.loadFromFile("Fonts/slkscr.ttf"))
	{
		std::cout << "ERROR::SETTINGSSTATE::COULD NOT LOAD FONT" << std::endl;
	}

}

void SettingsState::initGui()
{
	this->buttons["BACK"] = new gui::Button
	(
		1515.f, 550.f + 3.f * 120.f, 250.f, 80.f, &this->font, "Back", 30, sf::Color(70, 70, 70), sf::Color(100, 100, 100), sf::Color(150, 150, 150)
	);

	this->buttons["APPLY"] = new gui::Button
	(
		1215.f, 550.f + 3.f * 120.f, 250.f, 80.f, &this->font, "Apply", 30, sf::Color(70, 70, 70), sf::Color(100, 100, 100), sf::Color(150, 150, 150)
	);

	std::vector<std::string> modes_str;

	for (auto &i : this->modes)
	{
		modes_str.push_back(std::to_string(i.width) + "x" + std::to_string(i.height));
	}

	this->sliders["RESOLUTION"] = new gui::Slider(850.f, 510.f, 30.f, font, modes_str.data(), static_cast<int>(modes_str.size()));

	this->sliders["FULLSCREEN"] = new gui::Slider(850.f, 510.f + 1.f * 60.f, 30.f, font, fullscreenSettings.data(), static_cast<int>(fullscreenSettings.size()));

	this->sliders["FRAMERATE_LIMIT"] = new gui::Slider(850.f, 510.f + 2.f * 60.f, 30.f, font, framerateLimitSettings.data(), static_cast<int>(framerateLimitSettings.size()));

	this->sliders["VSYNC"] = new gui::Slider(850.f, 510.f + 3.f * 60.f, 30.f, font, vsyncSettings.data(), static_cast<int>(vsyncSettings.size()));

	this->sliders["ANTI_ALIASING"] = new gui::Slider(850.f, 510.f + 4.f * 60.f, 30.f, font, antiAliasingSettings.data(), static_cast<int>(antiAliasingSettings.size()));
}

void SettingsState::initText()
{
	this->settingsText.setFont(this->font);
	this->settingsText.setPosition(sf::Vector2f(300.f, 510.f));
	this->settingsText.setCharacterSize(30);
	this->settingsText.setFillColor(sf::Color::White);

	this->settingsText.setString
	(
		"Resolution \n\nFullscreen \n\nFramerate limit \n\nVsync \n\nAnti-aliasing"
	);

}

//Constructors and destructors
SettingsState::SettingsState(StateData* state_data) : State(state_data)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initGui();
	this->initText();
}

SettingsState::~SettingsState()
{
	//Deleting buttons
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}

	//Deleting sliders
	auto it2 = this->sliders.begin();
	for (it2 = this->sliders.begin(); it2 != this->sliders.end(); ++it2)
	{
		delete it2->second;
	}
}

//Functions
void SettingsState::updateGui(const float& dt)
{
	//Buttons
	for (auto it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	//Button functionality
	//Quiting the game
	if (this->buttons["BACK"]->isActive())
	{
		this->endState();
	}

	//Apply settings
	if (this->buttons["APPLY"]->isActive())
	{
		this->stateData->gfxSettings->resolution = this->modes[this->sliders["RESOLUTION"]->getActiveElementId()];

		this->window->create(this->stateData->gfxSettings->resolution, this->stateData->gfxSettings->title, sf::Style::Close | sf::Style::Titlebar);
	}

	//Sliders
	for (auto it : this->sliders)
	{
		it.second->update(this->mousePosView, dt);
	}

	//Slider functionality

}

void SettingsState::updateInput(const float& dt)
{
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		this->endState();
	}*/
}

void SettingsState::update(const float& dt)
{
	this->updateMousePos();

	this->updateInput(dt);

	this->updateGui(dt);
}

void SettingsState::renderGui(sf::RenderTarget& target)
{
	for (auto it : this->buttons)
	{
		it.second->render(target);
	}

	for (auto it : this->sliders)
	{
		it.second->render(target);
	}
}

void SettingsState::render(sf::RenderTarget& target)
{
	target.draw(this->background);

	this->renderGui(target);

	target.draw(this->settingsText);
}
