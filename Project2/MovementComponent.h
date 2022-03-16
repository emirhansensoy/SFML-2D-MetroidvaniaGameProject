#pragma once

enum movement_states {IDLE, MOVING, RUNNING_RIGHT, RUNNING_LEFT, JUMPING_RIGHT, JUMPING_LEFT, FALLING_RIGHT, FALLING_LEFT, ROLLING_RIGHT, ROLLING_LEFT};

class MovementComponent
{
private:
	//Variables
	sf::Sprite& sprite;

	sf::Vector2f velocity;
	float acceleration;
	float deceleration;
	float maxVelocity;

	//Private functions

public:
	//Constructors and destructors
	MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration);
	~MovementComponent();


	//Accessors
	const float& getMaxVelocity() const;
	const sf::Vector2f& getVelocity() const;
	

	//Functions
	const bool getState(const unsigned short state) const;

	void move(const float dir_x, const float dir_y, const float& dt);
	void update(const float& dt);

};

