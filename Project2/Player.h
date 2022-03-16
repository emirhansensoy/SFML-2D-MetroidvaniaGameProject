#pragma once

#include "Entity.h"

class Player : public Entity
{
private:
	//Variables
	bool attacking;

	//Private functions
	void initVariables();
	void initComponents();
	
public:
	//Contructors and destructors
	Player(float x, float y, sf::Texture& textureSheet);
	~Player();

	//Functions
	void updateAttack();
	void updateAnimation(const float& dt);
	virtual void update(const float& dt);
};

