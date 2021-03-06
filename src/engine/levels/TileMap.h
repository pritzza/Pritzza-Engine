#pragma once

#include <vector>

#include "../resource manager/ResourceManager.h"

#include "Tile.h"

class TileMap
{
private:
	std::vector<Tile> tiles;

	unsigned int width;
	unsigned int height;

public:
	void init(const sf::Vector2u& d, const ResourceManager<TEXTURE, sf::Texture>& tm);

	const std::vector<Tile>& getTiles() const;

};