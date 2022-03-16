#pragma once

class Tile
{
private:
	//Variables


	//Private functions


protected:
	sf::RectangleShape shape;


public:
	//Contructors and destructors
	Tile();
	Tile(float x, float y, float gridSizeF);
	~Tile();

	//Functions
	void update();
	void render(sf::RenderTarget& target);

};

