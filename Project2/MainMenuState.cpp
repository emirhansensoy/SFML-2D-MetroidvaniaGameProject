#include "stdafx.h"
#include "MainMenuState.h"

//Private functions
void MainMenuState::initVariables()
{

}

void MainMenuState::initBackground()
{
	this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));

	if (!this->bgTex.loadFromFile("Images/backgroundTexture.png"))
	{
		std::cout << "ERROR::MAIN_MENU_STATE::COULD NOT LOAD BG_TEX" << std::endl;
	}

	this->background.setTexture(&this->bgTex);
}

void MainMenuState::initFonts()
{
	if (!font.loadFromFile("Fonts/slkscr.ttf"))
	{
		std::cout << "ERROR::MAINMENUSTATE::COULD NOT LOAD FONT" << std::endl;
	}

}

void MainMenuState::initButtons()
{
	this->buttons["GAME_STATE"] = new gui::Button
	(
		200.f, 525.f + 0.f * 120.f, 400.f, 80.f, &this->font, "New Game", 30, sf::Color(70, 70, 70), sf::Color(100, 100, 100), sf::Color(150, 150, 150)
	);

	this->buttons["SETTINGS_STATE"] = new gui::Button
	(
		200.f, 525.f + 1.f * 120.f, 400.f, 80.f, &this->font, "SETTINGS", 30, sf::Color(70, 70, 70), sf::Color(100, 100, 100), sf::Color(150, 150, 150)
	);

	this->buttons["EDITOR_STATE"] = new gui::Button
	(
		200.f, 525.f + 2.f * 120.f, 400.f, 80.f, &this->font, "EDITOR", 30, sf::Color(70, 70, 70), sf::Color(100, 100, 100), sf::Color(150, 150, 150)
	);

	this->buttons["QUIT_STATE"] = new gui::Button
	(
		200.f, 525.f + 3.f * 120.f, 400.f, 80.f, &this->font, "Quit", 30, sf::Color(70, 70, 70), sf::Color(100, 100, 100), sf::Color(150, 150, 150)
	);
}

//Constructors and destructors
MainMenuState::MainMenuState(StateData* state_data) : State(state_data)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initButtons();
}

MainMenuState::~MainMenuState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

//Functions
void MainMenuState::updateButtons()
{
	for (auto it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	//Starting a new game
	if (this->buttons["GAME_STATE"]->isActive())
	{
		this->states->push(new GameState(this->stateData));
	}

	//Settings
	if (this->buttons["SETTINGS_STATE"]->isActive())
	{
		this->states->push(new SettingsState(this->stateData));
	}

	//Editor
	if (this->buttons["EDITOR_STATE"]->isActive())
	{
		this->states->push(new EditorState(this->stateData));
	}

	//Quiting the game
	if (this->buttons["QUIT_STATE"]->isActive())
	{
		this->endState();
	}
}

void MainMenuState::updateInput(const float& dt)
{
	
}

void MainMenuState::update(const float& dt)
{
	this->updateMousePos();

	this->updateInput(dt);

	this->updateButtons();
}

void MainMenuState::renderButtons(sf::RenderTarget& target)
{
	for (auto it : this->buttons)
	{
		it.second->render(target);
	}
}

void MainMenuState::render(sf::RenderTarget& target)
{
	target.draw(this->background);

	this->renderButtons(target);
}
