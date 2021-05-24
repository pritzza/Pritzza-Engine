#include "Entity.h"

#include <math.h>

// needs refactor
void Entity::init(const sf::Vector2f& pos, const sf::Vector2i& dimensions)
{
	this->pos = pos;
	this->vel = sf::Vector2f(0, 0);
	this->acc = sf::Vector2f(1, 1);

	this->setSize(dimensions);
}

void Entity::init(const sf::Vector2f& pos, const sf::Vector2i& dimensions, const sf::Texture& t)
{
	this->pos = pos;
	this->vel = sf::Vector2f(0, 0);
	this->acc = sf::Vector2f(30.f, 30.f);

	this->setSize(dimensions);
	this->setTexture(t);
}

void Entity::init(const sf::Vector2f& pos, const sf::Vector2i& dimensions, const sf::Texture& t, const sf::Vector2i& shDimensions, const float maxFrameDur)
{
	this->pos = pos;
	this->vel = sf::Vector2f(0, 0);
	this->acc = sf::Vector2f(30.f, 30.f);

	this->setSize(dimensions);
	this->setTexture(t);

	this->sprite.setIsAnimated(true);
	this->sprite.setKeyFrameMaxDuration(maxFrameDur);
	this->sprite.setSpriteSheetDimensions(shDimensions);
}

void Entity::update(const float dt)
{
	this->updatePhysics(dt);
	this->updatePos(dt);

	this->updateDirection(this->vel);

	this->box.update(this->pos);
	this->sprite.update(this->pos, dt, this->direction, this->isMoving);

	isMoving = false;
}

void Entity::updatePhysics(const float dt)
{
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
	this->vel.x *= 1.f - (DECELERATION_RATE * dt);
	this->vel.y *= 1.f - (DECELERATION_RATE * dt);

	if (!isMoving)
	{
		if (vel.x < MIN_VEL && vel.x > 0)
			vel.x = 0;
		else if (vel.x > -MIN_VEL && vel.x < 0)
			vel.x = 0;

		if (vel.y < MIN_VEL && vel.y > 0)
			vel.y = 0;
		else if (vel.y > -MIN_VEL && vel.y < 0)
			vel.y = 0;
	}
}

void Entity::updatePos(const float dt)
{
	this->setPos({
		pos.x + (vel.x * dt),
		pos.y + (vel.y * dt)
		});
}

void Entity::updateDirection(const sf::Vector2f& v)
{
	if (this->isMoving)
	{
		bool isHorizontal{ abs(v.x) > abs(v.y) };	// change to >= for horizontal bias
		bool isPositive{ (isHorizontal && v.x > 0) || (!isHorizontal && v.y > 0) };

		if (isHorizontal && isPositive)
			this->direction = Direction::RIGHT;
		else if (isHorizontal && !isPositive)
			this->direction = Direction::LEFT;
		else if (!isHorizontal && isPositive)
			this->direction = Direction::DOWN;
		else if (!isHorizontal && !isPositive)
			this->direction = Direction::UP;
	}
}

void Entity::move(const sf::Vector2f& v)
{
	this->vel.x += v.x * this->acc.x;
	this->vel.y += v.y * this->acc.y;

	this->isMoving = true;
}

void Entity::setAcceleration(const sf::Vector2f acc) { this->acc = acc; }

const sf::Vector2f& Entity::getVel() const { return this->vel; }
