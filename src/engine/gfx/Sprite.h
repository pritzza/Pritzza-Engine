#pragma once

#include <SFML/Graphics.hpp>

#include "../util/Direction.h"

class Sprite
{
protected:
	sf::IntRect sbox;	// TextureRect
	sf::Sprite sprite;

protected:
	void setSpritePos(const sf::Vector2f& pos);

public:
	Sprite() {};
	Sprite(const sf::Vector2f& pos, const sf::Vector2i& dimensions, const sf::Texture& texture, const sf::Color& debugColor = { 0,0,0,0 });

	virtual void update(const sf::Vector2f& pos, const float dt = 0.f, const Direction& dir = Direction::UP, const bool isMoving = false);	// dt set to 0 so non animated sprites dont require dt

	void setTexture(const sf::Texture& texture);
	void setCrop(const sf::Vector2i& dimensions, const sf::Vector2i& pos = { 0,0 });
	void setColor(const sf::Color& color);

	const sf::Vector2f& getPos() const;
	const sf::Vector2i getDimensions() const;

	const sf::Sprite& getSprite() const;
	sf::Sprite& getSprite();
};