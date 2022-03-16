#pragma once

#include "Tile.h"

class Tilemap
{
private:
	//Variables
	float gridSizeF;
	unsigned gridSizeU;
	unsigned layers;
	sf::Vector2u maxSize;
	std::vector <std::vector <std::vector <Tile*> > > map;

	//Private functions



public:
	//Contructors and destructors
	Tilemap(float gridSize, unsigned width, unsigned height);
	~Tilemap();

	//Functions
	void update();
	void render(sf::RenderTarget& target);

	void addTile(const unsigned x, const unsigned y, const unsigned z);
	void removeTile();

};

