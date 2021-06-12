#pragma once

#include <unordered_map>
#include <memory>

// be sure that there is a switch condition for every resource added
enum class TEXTURE
{
	ERROR,
	DEFAULT,
	FROG_SPRITE_SHEET,
	SNAIL_SPRITE_SHEET,
	TILES,
	TILES_ISOMETRIC
};
enum class FONT
{
	ERROR,
	DEFAULT
};
enum class SOUND
{
	ERROR,
	DEFAULT,
	HIT
};
enum class MUSIC
{
	ERROR,
	DEFAULT
};

template <class Key, class Resource>
class ResourceManager
{
private:
	std::unordered_map<Key, Resource> resources;

private:
	virtual const Key loadFromFile(const std::string& fileName, const Key resID)
	{
		if (this->resources.find(resID) == resources.end())	// res not already loaded
		{
			Resource res;

			if (res.loadFromFile(fileName))	// if loaded sucessfully, insert and return id
			{
				// shout out to Herrad for his hard work debugging my terrible code
				this->resources.insert({ resID, res });
				return resID;
			}
			else // if couldnt find file, return default id
				return Key::DEFAULT;
		}

		return resID;	// if already loaded, do nothing and return id
	}

public:
	ResourceManager()
	{
		this->load(Key::ERROR);	// error resources automatically
	}

	const Key load(const TEXTURE id)
	{
		switch (id)
		{
		case TEXTURE::DEFAULT:				return loadFromFile("res/textures/img.png", id);
		case TEXTURE::FROG_SPRITE_SHEET:	return loadFromFile("res/textures/frog spritesheet.png", id);
		case TEXTURE::SNAIL_SPRITE_SHEET:	return loadFromFile("res/textures/snail sprite sheet.png", id);
		case TEXTURE::TILES:				return loadFromFile("res/textures/frog game tiles.png", id);
		case TEXTURE::TILES_ISOMETRIC:		return loadFromFile("res/textures/frog game tiles ISOMETRIC.png", id);

		default:							return loadFromFile("res/textures/richardd.png", id);	// error resource should always be loaded
		}
	}

	const Key load(const FONT id)
	{
		switch (id)
		{
		case FONT::DEFAULT:		return loadFromFile("res/fonts/Roboto-ThinItalic.ttf", id);

		default:				return loadFromFile("res/fonts/pokemon_fire_red.ttf", id);	// error resource should always be loaded
		}
	}

	const Key load(const SOUND id)
	{
		switch (id)
		{
		case SOUND::DEFAULT:	return loadFromFile("res/audio/ruby_000B.wav", id);
		case SOUND::HIT:		return loadFromFile("res/audio/ruby_00DE.wav", id);

		default:				return loadFromFile("res/audio/ruby_00EA.wav", id);	// error resource should always be loaded
		}
	}

	const Key load(const MUSIC id)
	{
		switch (id)
		{
		case MUSIC::DEFAULT:	return loadFromFile("res/audio/ruby_000B.wav", id);

		default:				return loadFromFile("res/audio/ruby_00EA.wav", id);	// error resource should always be loaded
		}
	}

	void unload(const Key id)
	{
		this->resources.erase(id);
	}

	const Resource& get(const Key id) const
	{
		if (resources.find(id) != resources.end())
			return resources.at(id);

		return resources.at(Key::ERROR);
	}
};