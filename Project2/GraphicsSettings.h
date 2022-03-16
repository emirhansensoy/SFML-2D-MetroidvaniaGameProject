#pragma once

class GraphicsSettings
{
public:
	//Variables
	std::string title;
	sf::VideoMode resolution;
	bool fullscreen;
	bool vsync;
	unsigned framerateLimit;
	sf::ContextSettings contextSettings;
	std::vector<sf::VideoMode> videoModes;


	GraphicsSettings();

	//Functions
	void saveToFile(const std::string path);
	void loadFromFile(const std::string path);
};