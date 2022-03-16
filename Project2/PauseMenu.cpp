#include "stdafx.h"
#include "PauseMenu.h"

//Constructors and destructors
PauseMenu::PauseMenu(sf::RenderWindow& window, sf::Font& font) : font(font)
{
	//Init background
	this->background.setSize(sf::Vector2f(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)));
	this->background.setFillColor(sf::Color(20, 20, 20, 100));

	//Init container
	this->container.setSize(sf::Vector2f(static_cast<float>(window.getSize().x / 2.f), static_cast<float>(window.getSize().y)));
	this->container.setFillColor(sf::Color(20, 20, 20, 200));
	this->container.setPosition(static_cast<float>(window.getSize().x) / 2.f - this->container.getSize().x / 2.f, 0.f);

	//Init text
	this->menuText.setFont(font);
	this->menuText.setFillColor(sf::Color(255, 255, 255, 200));
	this->menuText.setCharacterSize(60);
	this->menuText.setString("PAUSED");
	this->menuText.setPosition(this->container.getPosition().x + this->container.getSize().x / 2.f - this->menuText.getGlobalBounds().width / 2.f, this->container.getPosition().y + 50.f);

}

PauseMenu::~PauseMenu()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

//Accessors
std::map<std::string, gui::Button*>& PauseMenu::getButtons()
{
	return this->buttons;
}

const bool PauseMenu::isButtonPressed(const std::string key)
{
	return this->buttons[key]->isActive();
}

//Functions
void PauseMenu::addButtons(const std::string key, float y, const std::string text)
{
	float width = 400.f;
	float height = 80.f;
	float x = this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f;

	this->buttons[key] = new gui::Button
	(
		x, y, width, height, &this->font, text, 30, sf::Color(70, 70, 70), sf::Color(100, 100, 100), sf::Color(150, 150, 150)
	);
}

void PauseMenu::update(sf::Vector2f& mousePos)
{
	for (auto i : this->buttons)
	{
		i.second->update(mousePos);
	}
}

void PauseMenu::render(sf::RenderTarget& target)
{
	target.draw(background);
	target.draw(container);

	for (auto it : this->buttons)
	{
		it.second->render(target);
	}

	target.draw(this->menuText);
}

