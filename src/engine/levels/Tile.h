#pragma once

#include "../gfx/Sprite.h"

enum class TileType
{
	GRASS,
	WATER,
	SAND,
	BUSH,
	MOUNTAIN,
	WEIRD,

	NUM_TILES
};

enum TILE_COORDS
{
	// y == 0
	GRASS_X = 0,
	GRASS_Y = 0,

	WATER_X = 1,
	WATER_Y = 0,

	WEIRD_X = 2,
	WEIRD_Y = 0,

	// y == 1
	BUSH_X = 0,
	BUSH_Y = 1,

	SAND_X = 1,
	SAND_Y = 1,

	MOUNTAIN_X = 2,
	MOUNTAIN_Y = 1,
};

class Tile
{
public:
	static constexpr int NULL_BUSH_ID{ -1 };

private:
	const int WIDTH{ 16 };	// px
	const int HEIGHT{ 8 };

private:
	TileType tileType;
	Sprite sprite;

	int elevation;

	int bushID{ NULL_BUSH_ID };	// if not a bush, set to -1 by default

private:
	void initSprite(const int i, const unsigned int w, const sf::Texture& t);

public:
	void init(const TileType tileType, const int elevationconst, const int index, const unsigned int mapWidth, const sf::Texture& t);

	void setTileType(const TileType tileType);
	void setBushID(const int id);

	const TileType getTileType() const;
	const int getBushID() const;
	const sf::Vector2i& getDimensions() const;
	const Sprite& getSprite() const;
};