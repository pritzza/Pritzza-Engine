#pragma once

#include "../gfx/Sprite.h"

enum class Tiles
{
	GRASS,
	WATER,
	LILY,
	LOG,
	NUM_TILES
};

class Tile
{
private:
	static constexpr unsigned int LENGTH{ 16 };	// px

private:
	bool solid;
	Sprite sprite;

public:
	void init(const bool solid, const int index, const unsigned int mapWidth, const sf::Texture& t, const Tiles tileType);

	constexpr unsigned int getLength() const;

	const Sprite& getSprite() const;
};