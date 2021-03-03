#include "Sprite.h"

#include <iostream>

Sprite::Sprite(const sf::Vector2f& pos, const unsigned width, const unsigned height)
	:
	sbox{ 0, 0, width, height },
	pos{ pos }
{
	s.setTextureRect(sbox);
}

void Sprite::update()
{
	std::cout << "Sprite:" << pos.x << ", " << pos.y << '\n';
	this->setPos(this->pos);
}

void Sprite::setTexture(const sf::Texture& t)
{
	this->s.setTexture(t);
}

void Sprite::setPos(const sf::Vector2f& p)
{
	this->s.setPosition(p);
}

const sf::Sprite& Sprite::getSprite() const		{ return this->s;	 }