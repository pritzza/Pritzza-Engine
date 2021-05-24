#pragma once

#include "../gfx/AnimatedSprite.h"
#include "../util/AABB.h"

class GameObject
{
protected:
	sf::Vector2f pos;

	AABB box;
	AnimatedSprite sprite;

public:
	// needs refactor
	virtual void init(const sf::Vector2f& pos, const sf::Vector2i& dimensions);
	virtual void init(const sf::Vector2f& pos, const sf::Vector2i& dimensions, const sf::Texture& t);
	virtual void init(const sf::Vector2f& pos, const sf::Vector2i& dimensions, const sf::Texture& t, const sf::Vector2i& shDimensions, const float maxFrameDur);

	virtual void update(const float dt);

	const bool isColliding(const GameObject& e) const;

	void setSize(const sf::Vector2i& size);
	void setPos(const sf::Vector2f pos);
	void setTexture(const sf::Texture& texture);

	const sf::Vector2f& getPos() const;
	const sf::Vector2f getCenterPos() const;

	Sprite& getSprite();
	const Sprite& getSprite() const;

	const sf::Sprite& getSFSprite() const;

	const AABB& getAABB() const;
	const sf::RectangleShape getRect() const;
};