#pragma once

#include <SFML/Graphics.hpp>

class Sprite
{
protected:
	sf::IntRect sbox;	// TextureRect
	sf::Sprite s;

private:
	void setSpritePos(const sf::Vector2f& pos);

public:
	Sprite() {};
	Sprite(const sf::Vector2f& pos, const sf::Vector2u& dimensions, const sf::Texture& texture);

	void update(const sf::Vector2f& pos);	// dt set to 0 so non animated sprites dont require dt

	void setTexture(const sf::Texture& texture);

	void setDimensions(const sf::Vector2u& dimensions);

	const sf::Vector2f& getPos() const;

	const sf::Sprite& getSprite() const;
};