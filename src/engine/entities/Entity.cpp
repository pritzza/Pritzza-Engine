#include "Entity.h"

#include <iostream>

Entity::Entity()
	:
	pos{ 10,15 },
	vel{ 0,0 },
	box{ pos, 20, 20 },
	sprite{ pos, 16, 16 }
{
	update();
	std::cout << pos.x << " " << pos.y << " " << sprite.getSprite().getPosition().x << " " << sprite.getSprite().getPosition().y << '\n';
}

void Entity::update()
{
	this->updatePos();

	this->box.update();
	this->sprite.update();
}

void Entity::updatePos()
{
	std::cout << "Entity:" << pos.x << ", " << pos.y << "\n\n";
	this->setPos({ pos.x + vel.x, pos.y + vel.y });
}

void Entity::setTexture(const sf::Texture& texture)
{
	this->sprite.setTexture(texture);
}

void Entity::setPos(const sf::Vector2f& pos)
{
	this->box.setPos(pos);
}

void Entity::move(const sf::Vector2f& v)
{
	//std::cout << vel.x << ' ' << vel.y << '\n';

	this->vel += v;
}

const sf::Vector2f& Entity::getPos() const
{
	return this->box.getPos();
}

const Sprite& Entity::getSprite()
{
	return this->sprite;
}

const sf::Sprite& Entity::getSFSprite()
{
	return this->sprite.getSprite();
}

const AABB& Entity::getAABB()
{
	return this->box;
}

const sf::RectangleShape Entity::getRect()
{
	return this->box.getRect();
}
