#pragma once

#include <unordered_map>
#include <memory>

enum class TEXTURE
{
	ERROR,
	DEFAULT
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
	std::unordered_map<Key, std::shared_ptr<Resource>> resources;

public:
	ResourceManager()
	{
		this->load(Key::ERROR);	// error resources automatically
	}

	const Key load(const TEXTURE id)
	{
		switch (id)
		{
		case TEXTURE::ERROR:	return loadFromFile("res/textures/richardd.png", id);	// error resource should always be loaded
		case TEXTURE::DEFAULT:	return loadFromFile("res/textures/img.png", id);
		}
	}

	const Key load(const FONT id)
	{
		switch (id)
		{
		case FONT::ERROR:		return loadFromFile("res/fonts/pokemon_fire_red.ttf", id);	// error resource should always be loaded
		case FONT::DEFAULT:		return loadFromFile("res/fonts/Roboto-ThinItalic.ttf", id);
		}
	}

	const Key load(const AUDIO id)
	{
		switch (id)
		{
		case AUDIO::ERROR:		return loadFromFile("res/audio/001- EarthBound - Burp.mp3", id);	// error resource should always be loaded
		case AUDIO::DEFAULT:	return loadFromFile("res/audio/170- Earthbound - OK _Ssuka_.mp3", id);
		}
	}

	void unload(const Key id)
	{
		this->resources.erase(id);
	}

	const Resource& get(const Key id) const
	{
		if (resources.find(id) != resources.end())
			return *resources.at(id);

		return *resources.at(Key::ERROR);
	}

private:
	const Key loadFromFile(const std::string& fileName, const Key resID)
	{
		if (this->resources.find(resID) == resources.end())	// res not already loaded
		{
			std::shared_ptr<Resource> res = std::make_shared<Resource>();

			if (res->loadFromFile(fileName))	// if loaded sucessfully, insert and return id
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