#include "stdafx.h"
#include "State.h"

State::State(StateData* state_data) : quit(false), paused(false)
{
	this->stateData = state_data;
	this->window = state_data->window;
	this->states = state_data->states;
	this->gridSize = state_data->gridSize;
	this->keyTime = 0.f;
	this->keyTimeMax = 10.f;
}

State::~State()
{

}

//Accessors
const bool& State::getQuit() const
{
	return this->quit;
}

const bool State::getKeyTime()
{
	if (this->keyTime >= this->keyTimeMax)
	{
		this->keyTime = 0.f;
		return true;
	}

	return false;
}

//Functions
void State::endState()
{
	this->quit = true;
}

void State::pauseState()
{
	this->paused = true;
}

void State::unpauseState()
{
	this->paused = false;
}

void State::updateMousePos()
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
	this->mousePosGrid = sf::Vector2u
	(
		static_cast<unsigned>(this->mousePosView.x) / static_cast<unsigned>(this->gridSize), 
		static_cast<unsigned>(this->mousePosView.y) / static_cast<unsigned>(this->gridSize)
	);
}

void State::updateKeyTime(const float& dt)
{
	if (this->keyTime < this->keyTimeMax)
	{
		this->keyTime += 60.f * dt;

	}
}
