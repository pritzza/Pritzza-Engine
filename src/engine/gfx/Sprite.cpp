#include "Sprite.h"

Sprite::Sprite(const sf::Vector2f& pos, const sf::Vector2u& dimensions, const sf::Texture& texture)
{
	this->setSpritePos(pos);
	this->setDimensions(dimensions);
	this->setTexture(texture);
}

void Sprite::update(const sf::Vector2f& pos)
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

void Sprite::setDimensions(const sf::Vector2u& d)
{
	this->sbox = sf::IntRect(0, 0, d.x, d.y);
	this->s.setTextureRect(sbox);
}

const sf::Vector2f& Sprite::getPos() const  { return this->getSprite().getPosition(); }

const sf::Sprite& Sprite::getSprite() const { return this->s; }