#pragma once

#include "ResourceManager.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

struct ResourceManagers
{
	ResourceManager<TEXTURE, sf::Texture> textureManager;
	//ResourceManager<FONT, sf::Font> fontManager;
	//ResourceManager<AUDIO, sf::SoundBuffer> soundManager;
};