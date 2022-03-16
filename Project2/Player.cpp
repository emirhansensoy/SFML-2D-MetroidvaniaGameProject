#include "stdafx.h"
#include "Player.h"

//Private functions
void Player::initVariables()
{
	this->sprite.setScale(4.f, 4.f);
	this->attacking = false;
}

void Player::initComponents()
{

}

//Constructors and destructors
Player::Player(float x, float y, sf::Texture& textureSheet)
{
	this->initVariables();

	this->setPosition(x, y);

	this->createHitboxComponent(this->sprite, 72.f, 68.f, 92.f, 124.f);
	this->createMovementComponent(700.f, 50.f, 20.f);
	this->createAnimationComponent(textureSheet);

	this->animationComponent->addAnimation("IDLE", 13.f, 0, 5, 3, 5, 64, 64);
	this->animationComponent->addAnimation("RUNNING", 6.f, 0, 0, 7, 0, 64, 64);
	this->animationComponent->addAnimation("JUMPING", 0.f, 0, 7, 0, 7, 64, 64);
	this->animationComponent->addAnimation("FALLING", 0.f, 1, 7, 1, 7, 64, 64);
	this->animationComponent->addAnimation("ATTACK", 7.f, 0, 3, 6, 3, 64, 64);
}

Player::~Player()
{

}

//Funtions
void Player::updateAttack()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		this->attacking = true;
	}
}

void Player::updateAnimation(const float& dt)
{
	if (this->attacking)
	{
		

		if (this->animationComponent->play("ATTACK", dt, true))
		{
			this->attacking = false;

		}
	}
	if (this->movementComponent->getState(IDLE))
	{
		this->animationComponent->play("IDLE", dt);
	}
	else if (this->movementComponent->getState(RUNNING_RIGHT))
	{
		if (this->sprite.getScale().x < 0.f)
		{
			this->sprite.setOrigin(0.f, 0.f);
			this->sprite.setScale(4.f, 4.f);
		}

		this->animationComponent->play("RUNNING", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(RUNNING_LEFT))
	{
		if (this->sprite.getScale().x > 0.f)
		{
			this->sprite.setOrigin(59.f, 0.f);
			this->sprite.setScale(-4.f, 4.f);
		}

		this->animationComponent->play("RUNNING", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(JUMPING_RIGHT))
	{
		this->sprite.setOrigin(0.f, 0.f);
		this->sprite.setScale(4.f, 4.f);
		this->animationComponent->play("JUMPING", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
}

void Player::update(const float& dt)
{

	this->movementComponent->update(dt);

	this->updateAttack();
	
	this->updateAnimation(dt);

	this->hitboxComponent->update();
}


