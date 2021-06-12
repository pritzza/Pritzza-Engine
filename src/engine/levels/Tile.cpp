#include "Tile.h"

#include <iostream>
#include <math.h>

void Tile::init(const TileType tileType, const int elevation, const int i, const unsigned int w, const sf::Texture& texture)
{
	this->index = i;
	this->mapWidth = w;

	this->elevation = elevation;

	// getting pos
	const int x = index % mapWidth;
	const int y = index / mapWidth;

	this->pos = sf::Vector2f(
		static_cast<int>((x - y) * WIDTH  / 2),
		static_cast<int>((x + y) * HEIGHT / 2)
	);

	this->initSprite(i, w, texture);

	this->setTileType(tileType);
}

void Tile::update(const sf::Vector2i targetPos)
{
	const int distance = sqrt( pow( abs(targetPos.x - pos.x), 2 ) + pow( abs(targetPos.y - pos.y), 2 ));
	
	sf::Vector2f newPos(
		static_cast<int>(pos.x), 
		static_cast<int>(pos.y - elevation)
	);

	if (distance > RENDER_DISTANCE)
		newPos.y += static_cast<int>( ( pow( distance - RENDER_DISTANCE, 2 ) / (RENDER_DISTANCE * TILE_FADE_SMOOTHNESS) ) );

	//this->sprite.getSprite().setColor( sf::Color(255,255,255, 255.f / 1 ));

	this->sprite.update(newPos);
}

void Tile::initSprite(const int i, const unsigned int w, const sf::Texture& t)
{
	const sf::Vector2f elevatedPos{ pos.x, pos.y - elevation };
	const sf::Vector2i dimensions{ WIDTH, HEIGHT };

	this->sprite = Sprite(elevatedPos, dimensions, t);
}

void Tile::setTileType(const TileType tileType)
{
	this->tileType = tileType;

	const sf::Vector2i dimensions{ WIDTH, HEIGHT };

	sf::Vector2i spriteDisplacement;

	switch (tileType)
	{
	case TileType::GRASS:		spriteDisplacement = { GRASS_X    * WIDTH,		 GRASS_X    * HEIGHT };		break;
	case TileType::WATER:		spriteDisplacement = { WATER_X    * WIDTH,		 WATER_Y    * HEIGHT };		break;
	case TileType::SAND:		spriteDisplacement = { SAND_X     * WIDTH,		 SAND_Y	    * HEIGHT };		break;
	case TileType::BUSH:		spriteDisplacement = { BUSH_X     * WIDTH,		 BUSH_Y	    * HEIGHT };		break;
	case TileType::WEIRD:		spriteDisplacement = { WEIRD_X    * WIDTH, 		 WEIRD_Y	* HEIGHT };		break;
	case TileType::MOUNTAIN:	spriteDisplacement = { MOUNTAIN_X * WIDTH,		 MOUNTAIN_Y * HEIGHT };		break;
	}

	this->sprite.setCrop(dimensions, spriteDisplacement);
}

void Tile::setBushID(const int id) { this->bushID = id; }

const TileType Tile::getTileType() const { return this->tileType; }
const int Tile::getBushID() const { return this->bushID; }
const sf::Vector2i Tile::getDimensions() const { return sf::Vector2i{ WIDTH, HEIGHT }; }
const Sprite& Tile::getSprite() const { return this->sprite; }
