#include "ResourceManager.h"

/*	commented out because it dosent link

template <class Key, class Resource>
ResourceManager<Key, Resource>::ResourceManager()
{
	this->load(Key::ERROR);	// error resources automatically
}

template <class Key, class Resource>
const Key ResourceManager<Key, Resource>::load(const TEXTURE id)
{
	switch (id)
	{	
	case TEXTURE::ERROR:	return loadFromFile("res/textures/richardd.png", id);	// error resource should always be loaded
	case TEXTURE::DEFAULT:	return loadFromFile("res/textures/img.png", id);
	}
}

template <class Key, class Resource>
const Key ResourceManager<Key, Resource>::load(const FONT id)
{
	switch (id)
	{
	case FONT::ERROR:		return loadFromFile("res/fonts/pokemon_fire_red.ttf", id);	// error resource should always be loaded
	case FONT::DEFAULT:		return loadFromFile("res/fonts/Roboto-ThinItalic.ttf", id);
	}
}

template <class Key, class Resource>
const Key ResourceManager<Key, Resource>::load(const AUDIO id)
{
	switch (id)
	{
	case AUDIO::ERROR:		return loadFromFile("res/audio/001- EarthBound - Burp.mp3", id);	// error resource should always be loaded
	case AUDIO::DEFAULT:	return loadFromFile("res/audio/170- Earthbound - OK _Ssuka_.mp3", id);
	}
}

template <class Key, class Resource>
void ResourceManager<Key, Resource>::unload(const Key id)
{
	this->resources.erase(id);
}

template <class Key, class Resource>
const Resource& ResourceManager<Key, Resource>::get(const Key id) const
{
	if (resources.find(id) != resources.end())
		return *resources.at(id);

	return *resources.at(Key::ERROR);
}

template <class Key, class Resource>
const Key ResourceManager<Key, Resource>::loadFromFile(const std::string& fileName, const Key resID)
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

*/