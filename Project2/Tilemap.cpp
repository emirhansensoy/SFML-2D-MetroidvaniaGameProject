#include "stdafx.h"
#include "Tilemap.h"

//Private functions


//Constructors and destructors
Tilemap::Tilemap(float gridSize, unsigned width, unsigned height)
{
	this->gridSizeF = gridSize;
	this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
	this->layers = 1;
	this->maxSize.x = width;
	this->maxSize.y = height;

	this->map.resize(this->maxSize.x);

	for (size_t x = 0; x < this->maxSize.x; x++)
	{
		this->map.push_back(std::vector <std::vector <Tile*> >());

		for (size_t y = 0; y < this->maxSize.y; y++)
		{
			this->map[x].resize(this->maxSize.y);
			this->map[x].push_back(std::vector <Tile*>());

			for (size_t z = 0; z < this->layers; z++)
			{
				this->map[x][y].resize(this->layers);
				this->map[x][y].push_back(NULL);
			}
		}
	}
}

Tilemap::~Tilemap()
{
	for (size_t x = 0; x < this->maxSize.x; x++)
	{

		for (size_t y = 0; y < this->maxSize.y; y++)
		{

			for (size_t z = 0; z < this->layers; z++)
			{
				delete this->map[x][y][z];
			}
		}
	}
}

//Functions
void Tilemap::update()
{
}

void Tilemap::render(sf::RenderTarget& target)
{
	for (auto &x : this->map)
	{
		for (auto &y : x)
		{
			for (auto *z : y)
			{
				if (z != NULL)
				{
					z->render(target);
				}
			}
		}
	}
}

void Tilemap::addTile(const unsigned x, const unsigned y, const unsigned z)
{
	if (x < this->maxSize.x && x >= 0 && y < this->maxSize.y && y >= 0 && z < this->layers && z >= 0)
	{
		if (this->map[x][y][z] == NULL)//It needs to be empty to add a tile
		{
			this->map[x][y][z] = new Tile(x * this->gridSizeF, y * this->gridSizeF, this->gridSizeF);
		}
	}
}

void Tilemap::removeTile()
{

}


