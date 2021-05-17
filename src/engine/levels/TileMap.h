#pragma once

#include <vector>

#include "../resource manager/ResourceManager.h"

#include "Tile.h"

#include "../util/PerlinNoise.h"

class TileMap
{
private:
	const float MAP_SCALE{ 5.f };	// the biggest the scale, the more "zoomed out" the noise is

private:
	std::vector<Tile> tiles;

	unsigned int width;
	unsigned int height;

	siv::PerlinNoise perlinNoise;

private:
	const Tiles generateTile(const int i) const;

public:
	void init(const sf::Vector2u& d, const sf::Texture& tilesTexture);

	const std::vector<Tile>& getTiles() const;

};