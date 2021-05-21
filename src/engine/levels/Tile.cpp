#include "Tile.h"

#include <iostream>

void Tile::init(const TileType tileType, const int elevation, const int i, const unsigned int w, const sf::Texture& texture)
{
	this->tileType = tileType;
	this->elevation = elevation;

	this->initSprite(i, w, texture);

	this->setTileType(tileType);
}

void Tile::initSprite(const int i, const unsigned int w, const sf::Texture& t)
{
	//const sf::Vector2f pos = sf::Vector2f(
	//	( (i % w) * WIDTH ),
	//	( (i / w) * HEIGHT)
	//	);

	const int x = i % w;
	const int y = i / w;

	const sf::Vector2f pos = sf::Vector2f(
		(x - y) * (WIDTH  / 2),
		(x + y) * (HEIGHT / 2) - this->elevation
	);

	const sf::Vector2i dimensions{ WIDTH, HEIGHT };

	this->sprite = Sprite(pos, dimensions, t);
}

void Tile::setTileType(const TileType tileType)
{
	this->tileType = tileType;

	const sf::Vector2i dimensions{ WIDTH, HEIGHT };

	sf::Vector2i spriteDisplacement;

	switch (tileType)
	{
	case TileType::GRASS:		spriteDisplacement = { GRASS_X	  * WIDTH,		 GRASS_X    * HEIGHT };		break;
	case TileType::WATER:		spriteDisplacement = { WATER_X    * WIDTH,		 WATER_Y    * HEIGHT };		break;
	case TileType::SAND:		spriteDisplacement = { SAND_X     * WIDTH,		 SAND_Y     * HEIGHT };		break;
	case TileType::BUSH:		spriteDisplacement = { BUSH_X     * WIDTH,		 BUSH_Y     * HEIGHT };		break;
	case TileType::WEIRD:		spriteDisplacement = { WEIRD_X    * WIDTH, 		 WEIRD_Y    * HEIGHT };		break;
	case TileType::MOUNTAIN:	spriteDisplacement = { MOUNTAIN_X * WIDTH,		 MOUNTAIN_Y * HEIGHT };		break;
	}

	this->sprite.setCrop(dimensions, spriteDisplacement);
}

void Tile::setBushID(const int id) { this->bushID = id; }

const TileType Tile::getTileType() const		{ return this->tileType;				}
const int Tile::getBushID() const				{ return this->bushID;					}
const sf::Vector2i& Tile::getDimensions() const { return sf::Vector2i{ WIDTH, HEIGHT }; }
const Sprite& Tile::getSprite() const			{ return this->sprite;					}
