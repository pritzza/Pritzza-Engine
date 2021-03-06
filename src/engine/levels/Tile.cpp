#include "Tile.h"

void Tile::init(const bool solid, const int i, const unsigned int w, const sf::Texture& t)
{
	this->solid = solid;

	const sf::Vector2f pos = sf::Vector2f((i % w) * LENGTH, (i / w) * LENGTH);
	const sf::Vector2u dimensions{ LENGTH, LENGTH };

	this->sprite = Sprite(pos, dimensions, t);
}

constexpr unsigned int Tile::getLength() const  { return this->LENGTH; }

const Sprite& Tile::getSprite() const			{ return this->sprite; }
