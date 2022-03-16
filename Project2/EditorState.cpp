#include "stdafx.h"
#include "EditorState.h"

void EditorState::initVariables()
{

}

void EditorState::initFonts()
{
	if (!font.loadFromFile("Fonts/slkscr.ttf"))
	{
		std::cout << "ERROR::EDITORSTATE::COULD NOT LOAD FONT" << std::endl;
	}

}

void EditorState::initPauseMenu()
{
	this->pmenu = new PauseMenu(*this->window, this->font);
	this->pmenu->addButtons("QUIT", 920.f, "Quit");
}

void EditorState::initButtons()
{
	
}

void EditorState::initGui()
{
	this->selectorRect.setSize(sf::Vector2f(this->stateData->gridSize, this->stateData->gridSize));
	this->selectorRect.setFillColor(sf::Color::Transparent);
	this->selectorRect.setOutlineThickness(1.f);
	this->selectorRect.setOutlineColor(sf::Color::Green);
}

void EditorState::initTilemap()
{
	this->tileMap = new Tilemap(this->stateData->gridSize, 25, 25);
}

EditorState::EditorState(StateData* state_data) : State(state_data)
{
	this->initVariables();
	this->initFonts();
	this->initPauseMenu();
	this->initButtons();
	this->initGui();
	this->initTilemap();
}

EditorState::~EditorState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
	delete this->pmenu;
	delete this->tileMap;
}

void EditorState::updateButtons()
{
	for (auto it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

}

void EditorState::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonPressed("QUIT"))
	{
		this->endState();
	}
}

void EditorState::updateGui()
{
	this->selectorRect.setPosition(this->mousePosGrid.x * this->stateData->gridSize, this->mousePosGrid.y * this->stateData->gridSize);
}

void EditorState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && this->getKeyTime())
	{
		if (!this->paused)
		{
			this->pauseState();
		}
		else
		{
			this->unpauseState();
		}
	}
}

void EditorState::updateEditorInput(const float& dt)
{
	//Add a tile
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeyTime())
	{
		this->tileMap->addTile(this->mousePosGrid.x, this->mousePosGrid.y, 0);
	}
}

void EditorState::update(const float& dt)
{
	this->updateMousePos();
	this->updateKeyTime(dt);
	this->updateInput(dt);

	if (!this->paused)
	{
		this->updateButtons();
		this->updateGui();
		this->updateEditorInput(dt);
	}
	else//Paused update
	{
		this->pmenu->update(this->mousePosView);
		this->updatePauseMenuButtons();
	}
}

void EditorState::renderButtons(sf::RenderTarget& target)
{
	for (auto it : this->buttons)
	{
		it.second->render(target);
	}
}

void EditorState::renderGui(sf::RenderTarget& target)
{
	target.draw(this->selectorRect);
}

void EditorState::render(sf::RenderTarget& target)
{
	this->renderButtons(target);

	this->renderGui(target);

	this->tileMap->render(target);

	if (this->paused) //Pause menu render
	{
		this->pmenu->render(target);
	}
}
