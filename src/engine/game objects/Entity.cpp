#include "Entity.h"

void Entity::init(const sf::Vector2f& pos, const sf::Vector2u& dimensions)
{
	this->pos = pos;
	this->vel = sf::Vector2f(0, 0);
	this->acc = sf::Vector2f(30.f, 30.f);
	
	this->setSize(dimensions);
}

void Entity::update(const float dt)
{
	this->updatePhysics(dt);
	this->updatePos(dt);	

	this->box.update(this->pos);
	this->sprite.update(this->pos);
}

void Entity::updatePhysics(const float dt)
{
	constexpr float MAX_VEL{ 120.0f };

	// limit x vel
	if (vel.x > MAX_VEL)
		vel.x = MAX_VEL;
	else if (vel.x < -MAX_VEL)
		vel.x = -MAX_VEL;

	// limit y vel
	if (vel.y > MAX_VEL)
		vel.y = MAX_VEL;
	else if (vel.y < -MAX_VEL)
		vel.y = -MAX_VEL;

	// decelerate
	constexpr float DECELERATION_RATE{ 6.f };

	this->vel.x *= 1.f - (dt * DECELERATION_RATE);
	this->vel.y *= 1.f - (dt * DECELERATION_RATE);

	constexpr float MIN_VEL{ 2.f };

	//if (vel.x < MIN_VEL)
	//	vel.x = 0;
	//else if (vel.x > -MIN_VEL)
	//	vel.x = 0;
	//
	//if (vel.y < MIN_VEL)
	//	vel.y = 0;
	//else if (vel.y > -MIN_VEL)
	//	vel.y = 0;
}

void Entity::updatePos(const float dt)
{
	constexpr float MAX_VEL{ 2 };

	this->setPos( {pos.x + (vel.x * dt), pos.y + (vel.y * dt)} );
}

void Entity::move(const sf::Vector2f& v)
{
	this->vel.x += v.x * this->acc.x;
	this->vel.y += v.y * this->acc.y;
}

const sf::Vector2f& Entity::getVel() const
{
	return this->vel;
}
