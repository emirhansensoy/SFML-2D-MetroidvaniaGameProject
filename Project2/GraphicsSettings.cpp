#include "stdafx.h"
#include "GraphicsSettings.h"

//Constructors and destructors
GraphicsSettings::GraphicsSettings()
{
	this->title = "Default";
	this->resolution = sf::VideoMode::getDesktopMode();
	this->fullscreen = false;
	this->framerateLimit = 144;
	this->vsync = false;
	this->contextSettings.antialiasingLevel = 0;
	this->videoModes = sf::VideoMode::getFullscreenModes();
}

//Functions
void GraphicsSettings::saveToFile(const std::string path)
{
	std::ofstream ofs(path);

	if (ofs.is_open())
	{
		ofs << this->title;
		ofs << this->resolution.width << " " << this->resolution.height;
		ofs << fullscreen;
		ofs << framerateLimit;
		ofs << vsync;
		ofs << contextSettings.antialiasingLevel;
	}

	ofs.close();
}

void GraphicsSettings::loadFromFile(const std::string path)
{
	std::ifstream ifs(path);

	if (ifs.is_open())
	{
		std::getline(ifs, this->title);
		ifs >> this->resolution.width >> this->resolution.height;
		ifs >> fullscreen;
		ifs >> framerateLimit;
		ifs >> vsync;
		ifs >> contextSettings.antialiasingLevel;
	}

	ifs.close();
}