#pragma once

#include <SFML/Graphics.hpp>

class AABB
{
private:
	sf::IntRect cbox;
	sf::RectangleShape rect;

	const sf::Vector2f& pos;

public:
	AABB(const sf::Vector2f& pos, const unsigned width, const unsigned height);

	void update();

	void setPos(const sf::Vector2f& pos);

	bool isColliding(const AABB& target) const;

	const sf::Vector2f& getPos() const;
	const sf::IntRect& getBox() const;
	const sf::RectangleShape getRect() const;
};