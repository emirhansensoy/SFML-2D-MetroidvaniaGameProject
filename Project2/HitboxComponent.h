#pragma once

class HitboxComponent
{
private:
	//Variables
	sf::Sprite& sprite;
	sf::RectangleShape hitbox;
	float offsetX;
	float offsetY;

	//Private functions


public:
	//Constructors and destructors
	HitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height);
	~HitboxComponent();

	//Functions
	bool checkIntersect(const sf::FloatRect& frect);

	void update();
	void render(sf::RenderTarget& target);

};

