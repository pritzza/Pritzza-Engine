#include "Tile.h"

void Tile::init(const bool solid, const int i, const unsigned int w, const sf::Texture& t, const Tiles tileType)
{
	this->solid = solid;

	const sf::Vector2f pos = sf::Vector2f((i % w) * LENGTH, (i / w) * LENGTH);
	const sf::Vector2u dimensions{ LENGTH, LENGTH };

	sf::Vector2u spriteDisplacement;

	switch (tileType)
	{
		case Tiles::GRASS:	spriteDisplacement = { 0 * LENGTH, 0 * LENGTH };	break;
		case Tiles::WATER:	spriteDisplacement = { 1 * LENGTH, 0 * LENGTH };	break;
		case Tiles::LILY:	spriteDisplacement = { 0 * LENGTH, 1 * LENGTH };	break;
		case Tiles::LOG:	spriteDisplacement = { 1 * LENGTH, 1 * LENGTH };	break;
	}

	this->sprite = Sprite(pos, dimensions, t);
	this->sprite.setDimensions(dimensions, spriteDisplacement);
}

constexpr unsigned int Tile::getLength() const  { return this->LENGTH; }

const Sprite& Tile::getSprite() const			{ return this->sprite; }
