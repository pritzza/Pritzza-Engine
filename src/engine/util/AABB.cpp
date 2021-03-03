#include "AABB.h"

#include <iostream>

AABB::AABB(const sf::Vector2f& pos, const unsigned width, const unsigned height)
	:
	cbox{ 0, 0, width, height },
	pos{ pos },
	rect({ static_cast<float>(width), static_cast<float>(height) })
{
	rect.setOutlineThickness(.1f);
	rect.setFillColor(sf::Color(37, 15, 201, 169));
	update();
}

void AABB::update()
{
	std::cout << "AABB:" << pos.x << ", " << pos.y << '\n';

	this->setPos(this->pos);
}

void AABB::setPos(const sf::Vector2f& pos)
{
	this->rect.setPosition(pos);
}

bool AABB::isColliding(const AABB& target) const
{
	const int x1 = pos.x;
	const int y1 = pos.y;
	const int w1 = cbox.width;
	const int h1 = cbox.height;

	const int x2 = target.getPos().x;
	const int y2 = target.getPos().y;
	const int w2 = target.getBox().width;
	const int h2 = target.getBox().height;

	//std::cout << "x: " << x1 << " y: " << y1 << " w: " << w1 << " h: " << h1 << ' ';
	//std::cout << "x: " << x2 << " y: " << y2 << " w: " << w2 << " h: " << h2 << '\n';
	//
	return (x1 < x2 + w2 &&
		x1 + w1 > x2 &&
		y1 < y2 + h2 &&
		y1 + h1 > y2);

	//return cbox.intersects(target.getBounds());
}

const sf::Vector2f& AABB::getPos() const { return this->pos; }
const sf::IntRect& AABB::getBox() const { return this->cbox; }

const sf::RectangleShape AABB::getRect() const
{
	return this->rect;
}
