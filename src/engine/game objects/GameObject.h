#pragma once

#include "../gfx/Sprite.h"
#include "../util/AABB.h"

class GameObject
{
protected:
	sf::Vector2f pos;

	AABB box;
	Sprite sprite;

public:
	virtual void init(const sf::Vector2f& pos, const sf::Vector2u& dimensions);

	virtual void update(const float dt);

	const bool isColliding(const GameObject& e) const;

	void setSize(const sf::Vector2u& size);

	void setPos(const sf::Vector2f pos);

	void setTexture(const sf::Texture& texture);

	const sf::Vector2f& getPos() const;

	Sprite& getSprite();
	const Sprite& getSprite() const;

	const sf::Sprite& getSFSprite() const;

	const AABB& getAABB() const;
	const sf::RectangleShape getRect() const;
};