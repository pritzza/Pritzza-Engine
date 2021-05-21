#pragma once

#include "ResourceManager.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

struct ResourceManagers
{
	ResourceManager<TEXTURE, sf::Texture> textureManager;
	ResourceManager<SOUND, sf::SoundBuffer> soundManager;
	ResourceManager<FONT, sf::Font> fontManager;
	//ResourceManager<MUSIC, sf::Music> musicManager; //curse you sf::Music
};