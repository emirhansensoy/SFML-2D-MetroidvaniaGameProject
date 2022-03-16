#include "stdafx.h"
#include "MovementComponent.h"

//Contructors and destructors
MovementComponent::MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration) : sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration)
{

}

MovementComponent::~MovementComponent()
{

}

//Accessors
const float& MovementComponent::getMaxVelocity() const
{
	return this->maxVelocity;
}

const sf::Vector2f& MovementComponent::getVelocity() const
{
	return this->velocity;
}

//Functions
const bool MovementComponent::getState(const unsigned short state) const
{
	if (state == IDLE)
	{
		if (this->velocity.x == 0.f && this->velocity.y == 0.f)
		{
			return true;
		}
	}
	if (state == MOVING)
	{
		if (this->velocity.x != 0.f || this->velocity.y != 0.f)
		{
			return true;
		}
	}
	if (state == RUNNING_RIGHT)
	{
		if (this->velocity.x > 0.f)
		{
			return true;
		}
	}
	if (state == RUNNING_LEFT)
	{
		if (this->velocity.x < 0.f)
		{
			return true;
		}
	}
	if (state == JUMPING_RIGHT)
	{
		if (this->velocity.x > 0.f && this->velocity.y > 0.f)
		{
			return true;
		}
	}
	if (state == JUMPING_LEFT)
	{
		if (this->velocity.x < 0.f && this->velocity.y > 0.f)
		{
			return true;
		}
	}
	if (state == FALLING_RIGHT)
	{
		if (this->velocity.x > 0.f && this->velocity.y < 0.f)
		{
			return true;
		}
	}
	if (state == FALLING_LEFT)
	{
		if (this->velocity.x < 0.f && this->velocity.y < 0.f)
		{
			return true;
		}
	}
	if (state == ROLLING_RIGHT)
	{

	}
	if (state == ROLLING_LEFT)
	{

	}

	return false;
}

void MovementComponent::move(const float dir_x, const float dir_y, const float& dt)
{
	//Acceleration
	this->velocity.x += this->acceleration * dir_x;

}

void MovementComponent::update(const float& dt)
{
	//Deceleration
	if (this->velocity.x > 0.f)
	{
		//Max velocity check
		if (this->velocity.x > this->maxVelocity)
		{
			this->velocity.x = this->maxVelocity;
		}

		//Deceleration right movement
		this->velocity.x -= deceleration;

		if (this->velocity.x < 0.f)
		{
			this->velocity.x = 0.f;
		}
	}
	else if (this->velocity.x < 0.f)
	{
		//Max velocity check
		if (this->velocity.x < -this->maxVelocity)
		{
			this->velocity.x = -this->maxVelocity;
		}

		//Deceleration left movement
		this->velocity.x += deceleration;

		if (this->velocity.x > 0.f)
		{
			this->velocity.x = 0.f;
		}
	}

	//Final move
	this->sprite.move(this->velocity * dt);
}