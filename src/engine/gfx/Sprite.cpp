#include "Sprite.h"

#include "../util/Direction.h"

Sprite::Sprite(const sf::Vector2f& pos, const sf::Vector2i& dimensions, const sf::Texture& texture, const sf::Color& debugColor)
{
	this->setSpritePos(pos);
	this->setCrop(dimensions);
	this->setTexture(texture);

	if (debugColor.a)
		this->s.setColor(debugColor);
}

void Sprite::update(const sf::Vector2f& pos, const float dt=0.f, const Direction& dir=Direction::UP, const bool isMoving=false)
{
	this->setSpritePos(pos);
}

void Sprite::setSpritePos(const sf::Vector2f& pos)
{
	this->s.setPosition(pos);
}

void Sprite::setTexture(const sf::Texture& t)
{
	this->s.setTexture(t);
}

void Sprite::setCrop(const sf::Vector2i& d, const sf::Vector2i& pos)	// pos optional, set to { 0,0 } in header
{
	this->sbox = sf::IntRect(pos.x, pos.y, d.x, d.y);
	this->s.setTextureRect(sbox);
}

const sf::Vector2f& Sprite::getPos() const			{ return this->getSprite().getPosition();					}	
const sf::Vector2i& Sprite::getDimensions() const	{ return sf::Vector2i(this->sbox.width, this->sbox.height); }

const sf::Sprite& Sprite::getSprite() const			{ return this->s; }

sf::Sprite& Sprite::getSprite()
{
	return this->s;
}
