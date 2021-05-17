#pragma once

#include <unordered_map>
#include <memory>

// be sure that there is a switch condition for every resource added
enum class TEXTURE
{
	ERROR,
	DEFAULT,
	FROG_SPRITE_SHEET,
	TILES
};
enum class FONT
{
	ERROR,
	DEFAULT
};
enum class AUDIO
{
	ERROR,
	DEFAULT
};

template <class Key, class Resource>
class ResourceManager
{
private:
	std::unordered_map<Key, Resource> resources;

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
		case TEXTURE::TILES:				return loadFromFile("res/textures/frog game tiles.png", id);

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

	const Key load(const AUDIO id)
	{
		switch (id)
		{
		case AUDIO::DEFAULT:	return loadFromFile("res/audio/170- Earthbound - OK _Ssuka_.mp3", id);
		
		default:				return loadFromFile("res/audio/001- EarthBound - Burp.mp3", id);	// error resource should always be loaded
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

private:
	const Key loadFromFile(const std::string& fileName, const Key resID)
	{
		if (this->resources.find(resID) == resources.end())	// res not already loaded
		{
			Resource res;

			if (res.loadFromFile(fileName))	// if loaded sucessfully, insert and return id
			{
				this->resources.insert({ resID, res });
				return resID;
			}
			else // if couldnt find file, return default id
				return Key::DEFAULT;
		}

		return resID;	// if already loaded, do nothing and return id
	}
};