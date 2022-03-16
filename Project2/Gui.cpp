#include "stdafx.h"
#include "Gui.h"

//======================BUTTON===========================

//Constructors and destructors
gui::Button::Button(float x, float y, float width, float height, sf::Font* font, std::string text, unsigned character_size, sf::Color buttonIdleColor, sf::Color buttonHoverColor, sf::Color buttonActiveColor, sf::Color textIdleColor, sf::Color textHoverColor, sf::Color textActiveColor, short unsigned id)
{
	this->buttonState = BTN_IDLE;
	this->id = id;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(textIdleColor);
	this->text.setCharacterSize(character_size);
	this->text.setPosition(this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f - 2.f, this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height - 2.f);

	this->textIdleColor = textIdleColor;
	this->textHoverColor = textHoverColor;
	this->textActiveColor = textActiveColor;
	this->buttonIdleColor = buttonIdleColor;
	this->buttonHoverColor = buttonHoverColor;
	this->buttonActiveColor = buttonActiveColor;

	this->shape.setFillColor(this->buttonIdleColor);
}

gui::Button::~Button()
{

}

//Accessors
const bool gui::Button::isActive() const
{
	if (this->buttonState == BTN_ACTIVE)
	{
		return true;
	}

	return false;
}

const std::string gui::Button::getText() const
{
	return this->text.getString();
}

const int gui::Button::getIndexOfList(std::string list[], int len, std::string seek)
{
	for (int i = 0; i < len; ++i)
	{
		if (list[i] == seek) return i;
	}

	return -1;
}

const short unsigned& gui::Button::getId() const
{
	return this->id;
}

//Modifiers
void gui::Button::setText(const std::string text)
{
	this->text.setString(text);
}

void gui::Button::setId(const short unsigned id)
{
	this->id = id;
}

//Functions
void gui::Button::update(const sf::Vector2f& mousePos)
{
	this->buttonState = BTN_IDLE;

	if (this->shape.getGlobalBounds().contains(mousePos))
	{
		this->buttonState = BTN_HOVER;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = BTN_ACTIVE;
		}
	}

	if (this->text.getGlobalBounds().contains(mousePos))
	{
		this->buttonState = BTN_HOVER;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = BTN_ACTIVE;
		}
	}

	if (this->buttonState == BTN_IDLE)
	{
		this->shape.setFillColor(this->buttonIdleColor);
		this->text.setFillColor(this->textIdleColor);
	}
	else if (this->buttonState == BTN_HOVER)
	{
		this->shape.setFillColor(this->buttonHoverColor);
		this->text.setFillColor(this->textHoverColor);
	}
	if(this->buttonState == BTN_ACTIVE)
	{
		this->shape.setFillColor(this->buttonActiveColor);
		this->text.setFillColor(this->textActiveColor);
	}

}

void gui::Button::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
	target.draw(this->text);
}

//========================SLIDER===============================

//Contructors and destructors
gui::Slider::Slider(float x, float y, float height, sf::Font& font, std::string list[], int list_size) : font(font), keytime(0.f), keytimeMax(2.f)
{
	float width = 300.f;

	this->listSize = list_size;

	for (int i = 0; i < this->listSize; i++)
	{
		this->list[i] = list[i];
	}
		
	this->activeElement = new gui::Button
	(
		x, y, width, height,
		&this->font, this->list[0], 35,
		sf::Color(70, 70, 70, 0), sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0),
		sf::Color(255, 255, 255), sf::Color(255, 255, 255), sf::Color(255, 255, 255)
		
	);
	this->rightButton = new gui::Button
	(
		x + width, y, 30.f, height,
		&this->font, ">", 35,
		sf::Color(70, 70, 70, 0), sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0),
		sf::Color(255, 0, 0), sf::Color(180, 0, 0), sf::Color(120, 0, 0)

	);
	this->leftButton = new gui::Button
	(
		x - 30.f, y, 30.f, height,
		&this->font, "<", 35,
		sf::Color(70, 70, 70, 0), sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0),
		sf::Color(255, 0, 0), sf::Color(180, 0, 0), sf::Color(120, 0, 0)
	);
	
}

gui::Slider::~Slider()
{
	delete this->activeElement;
	delete this->rightButton;
	delete this->leftButton;
}

//Accessors
const bool gui::Slider::getKeytime()
{
	if (this->keytime >= this->keytimeMax)
	{
		this->keytime = 0.f;
		return true;
	}

	return false;
}

const unsigned short gui::Slider::getActiveElementId() const
{
	return this->activeElement->getId();
}

//Functions
void gui::Slider::updateKeytime(const float& dt)
{
	if (this->keytime < this->keytimeMax)
	{
		this->keytime += 10.f * dt;
	}
}

void gui::Slider::update(const sf::Vector2f& mousePos, const float& dt)
{
	this->updateKeytime(dt);

	this->activeElement->update(mousePos);
	this->rightButton->update(mousePos);
	this->leftButton->update(mousePos);

	if (this->rightButton->isActive() && this->getKeytime())
	{
		if (this->activeElement->getIndexOfList(this->list, this->listSize, activeElement->getText()) + 1 < this->listSize)
		{
			this->activeElement->setText(this->list[this->activeElement->getIndexOfList(this->list, this->listSize, activeElement->getText()) + 1]);
			this->activeElement->setId(this->activeElement->getId() + 1);
		}
	}
	if (this->leftButton->isActive() && this->getKeytime())
	{
		if (this->activeElement->getIndexOfList(this->list, this->listSize, activeElement->getText()) - 1 >= 0)
		{
			this->activeElement->setText(this->list[this->activeElement->getIndexOfList(this->list, this->listSize, activeElement->getText()) - 1]);
			this->activeElement->setId(this->activeElement->getId() - 1);
		}
	}
}

void gui::Slider::render(sf::RenderTarget& target)
{
	this->activeElement->render(target);
	this->rightButton->render(target);
	this->leftButton->render(target);
}
