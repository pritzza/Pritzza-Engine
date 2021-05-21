#pragma once

#include <vector>

#include "../resource manager/ResourceManager.h"

#include "Tile.h"

#include "../util/PerlinNoise.h"

class TileMap
{
private:
	const float MAP_SCALE{ 50.f };	// the biggest the scale, the more "zoomed out" the noise is

	const unsigned int MAP_MAX_HEIGHT{ 128 };

	const float SEA_LEVEL{ 2.5f };

	const float BUSH_SCALE{ 15.f };	// the larger, the smaller the bush patch sizes
	const float BUSH_THRESHOLD{ 10.f / BUSH_SCALE };	// the lower, the more common

private:
	std::vector<Tile> tiles;

	std::vector<std::vector<int>> bushIndexes;

	int width;
	int height;

	siv::PerlinNoise perlinNoise;

private:
	const TileType generateTile(const float noise) const;
	const int generateElevation(const float noise) const;

	const void generateBushes();

	const bool isNearbyBush(const int x, const int y, const Tile* t) const;

public:
	TileMap();

	void init(const sf::Vector2u& d, const sf::Texture& tilesTexture);

	const std::vector<Tile>& getTiles() const;
	const Tile& getTile(const int i) const;
	const Tile& getTile(const int x, const int y) const;

};