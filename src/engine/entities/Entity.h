#pragma once

#include "../gfx/Sprite.h"
#include "../util/AABB.h"

class Entity
{
private:
	sf::Vector2f pos;
	sf::Vector2f vel;
	
	AABB box;
	Sprite sprite;

private:
	void updatePos();
	
public:
	Entity();

	void update();

	void setTexture(const sf::Texture& texture);
	
	void move(const sf::Vector2f& v);
	void setPos(const sf::Vector2f& pos);	// fix

	const sf::Vector2f& getPos() const;
	const Sprite& getSprite();
	const sf::Sprite& getSFSprite();
	const AABB& getAABB();
	const sf::RectangleShape getRect();
};