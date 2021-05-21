#include "TileMap.h"

#include <iostream>
#include <random>

TileMap::TileMap()
{
}

void TileMap::init(const sf::Vector2u& d, const sf::Texture& tilesTexture)
{
	// get rid of all of the grouped bushIndexes
	this->bushIndexes.clear();

	std::random_device seed;
	std::mt19937 rng(seed());
	this->perlinNoise.reseed(rng());

	this->width = d.x;
	this->height = d.y;

	if (tiles.size() != width * height)
		tiles.resize(width * height);

	for (int i = 0; i < width * height; ++i)
	{
		const double noise{ this->perlinNoise.noise2D_0_1
		(
			(i % width) / MAP_SCALE,
			(i / width) / MAP_SCALE
		)};

		tiles[i].init(generateTile(noise), generateElevation(noise), i, width, tilesTexture);
	}
	// want a differently seeded noise for bush gen
	this->perlinNoise.reseed(rng());

	this->generateBushes();

	//std::cout << bushIndexes.size() << ", " << bushIndexes[0].size() << '\n';
}

const void TileMap::generateBushes()
{
	// bush gen
	Tile* prevBush = nullptr;

	for (int i = 0; i < width * height; ++i)
	{
		const double bushNum{ perlinNoise.noise2D_0_1(
			(i % width) / BUSH_SCALE,
			(i / width) / BUSH_SCALE) 
		};

		if (bushNum > BUSH_THRESHOLD)
		{
			Tile& t{ tiles[i] };

			if (t.getTileType() != TileType::WATER && t.getTileType() != TileType::SAND)
				t.setTileType(TileType::BUSH);

			// stuff for bush patching/grouping
			//int bushGroupID{ Tile::NULL_BUSH_ID };
			//
			//// if there are any tiles around this one that are a bush
			//if (isNearbyBush(i % width, i / width, prevBush))
			//{
			//	bushGroupID = prevBush->getBushID();
			//}
			//else // if this is a new bush patch
			//{
			//	t.setTileType(TileType::WEIRD);
			//
			//	bushGroupID = bushIndexes.size();
			//	bushIndexes.push_back(std::vector<Tile*>());
			//}
			//
			//bushIndexes[bushGroupID].push_back(&t);
			//t.setBushID(bushGroupID);
			//prevBush = &t;
		}
	}
}

const TileType TileMap::generateTile(const float noise) const
{
	const float noiseNum = noise * static_cast<int>(TileType::NUM_TILES);

	// bottom values
	const float WATER{ SEA_LEVEL };
	const float SAND{ WATER + .25f };
	const float GRASS{ SAND + 2.5f };
	const float MOUNTAIN{ static_cast<int>(TileType::NUM_TILES) };	// upper bound

	if (noiseNum < WATER)
		return TileType::WATER;
	else if (noiseNum < SAND)
		return TileType::SAND;
	else if (noiseNum < GRASS)
		return TileType::GRASS;
	else if (noiseNum < MOUNTAIN)
		return TileType::MOUNTAIN;
	else
		std::cout << "out of bounds terrain gen: 0 < " << noiseNum << "< " << static_cast<int>(TileType::NUM_TILES) << '\n';

		return TileType::WEIRD;	
}

const int TileMap::generateElevation(const float noise) const
{
	const float elevation = noise * this->MAP_MAX_HEIGHT;

	if (elevation / MAP_MAX_HEIGHT > SEA_LEVEL / static_cast<int>(TileType::NUM_TILES))
		return elevation;
	else
		return (SEA_LEVEL / static_cast<int>(TileType::NUM_TILES)) * MAP_MAX_HEIGHT;
}

const bool TileMap::isNearbyBush(const int x, const int y, const Tile* t) const
{
	// if t == nullptr
	if (!t)
		return false;

	constexpr int SEARCH_DEPTH{ 7 };

	for (int i = 0; i < SEARCH_DEPTH; ++i)
		for (int j = -i; j < i ; ++j)
			for (int k = -i; k < i; ++k)
				if (getTile(x+j, y+k).getBushID() == t->getBushID())
					return true;

	return false;
}

const std::vector<Tile>& TileMap::getTiles() const { return this->tiles; }

const Tile& TileMap::getTile(const int i) const
{
	if (i >= 0 && i < tiles.size())
		return this->tiles[i];
	//else
		//std::cout << "out of bounds tilemap access\n";

	return this->tiles[0];
}

const Tile& TileMap::getTile(const int x, const int y) const
{
	if (x >= 0 && x < width && y >= 0 && y < height)
		return this->tiles[x + (width * y)];
	//else
	//	std::cout << "out of bounds tilemap access\n";

	return this->tiles[0];
}