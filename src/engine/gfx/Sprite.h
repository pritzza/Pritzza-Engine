#pragma once

#include <SFML/Graphics.hpp>

class Sprite
{
private:
	sf::IntRect sbox;	// TextureRect
	sf::Sprite s;

	const sf::Vector2f& pos;

private:
	void setSpritePos(const sf::Vector2f pos);

public:
	Sprite(const sf::Vector2f& pos, const unsigned width, const unsigned height);

	void update();

	void setTexture(const sf::Texture& t);

	const sf::Vector2f getPos() const;

	const sf::Sprite& getSprite() const;
};