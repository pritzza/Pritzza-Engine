#include "TileMap.h"

#include <iostream>

const Tiles TileMap::generateTile(const int i) const
{
	const float number = this->perlinNoise.noise2D_0_1
	(
		(i % width)/(width / MAP_SCALE), (i / width)/ (height / MAP_SCALE)
	) * static_cast<int>(Tiles::NUM_TILES);

	//std::cout << static_cast<int>(number);
	//
	//if (!(i % width))
	//	std::cout << '\n';

	switch (static_cast<int>(number))
	{
		case 2: return Tiles::GRASS;	// 2 is most common
		case 3: return Tiles::WATER;	// 3 is must less common
		case 0: return Tiles::LILY;		// 0 is very rare
		//case 1: return Tiles::LOG;	// 1 is pretty plentiful, comes in giant clumps
		default: //std::cout << "woops\n";

			return Tiles::WATER;
	}
}

void TileMap::init(const sf::Vector2u& d, const sf::Texture& tilesTexture)
{
	this->perlinNoise.reseed(123);

	this->width = d.x;
	this->height = d.y;

	tiles.resize(width * height);

	for (int i = 0; i < width * height; ++i)
	{
		tiles[i].init(false, i, width, tilesTexture, this->generateTile(i));
	}
}

const std::vector<Tile>& TileMap::getTiles() const { return this->tiles; }
