#include "TileMap.h"

void TileMap::init(const sf::Vector2u& d, const ResourceManager<TEXTURE, sf::Texture>& tm)
{
	this->width = d.x;
	this->height = d.y;

	tiles.resize(width * height);

	for (int i = 0; i < width * height; ++i)
		tiles[i].init(false, i, width, tm.get(TEXTURE::ERROR));
}

const std::vector<Tile>& TileMap::getTiles() const { return this->tiles; }
