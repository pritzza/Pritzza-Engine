#include "AABB.h"

#include <iostream>

AABB::AABB()
{
	rect.setOutlineThickness(1.f);
	rect.setFillColor(sf::Color::Transparent);
	rect.setOutlineColor(sf::Color(37, 15, 201, 169));
}

void AABB::update(const sf::Vector2f& pos)
{
	this->setRectPos(pos);
}

void AABB::setRectPos(const sf::Vector2f& p)
{
	this->rect.setPosition(p);
}

bool AABB::isColliding(const AABB& target) const
{
	const int x1 = this->getPos().x;
	const int y1 = this->getPos().y;
	const int w1 = this->getBox().width;
	const int h1 = this->getBox().height;

	const int x2 = target.getPos().x;
	const int y2 = target.getPos().y;
	const int w2 = target.getBox().width;
	const int h2 = target.getBox().height;

	return (
		x1 < x2 + w2 &&
		x1 + w1 > x2 &&
		y1 < y2 + h2 &&
		y1 + h1 > y2
		);
}

void AABB::setDimensions(const sf::Vector2u d)
{
	this->cbox = sf::IntRect(0, 0, d.x, d.y);
	this->rect.setSize( {static_cast<float>(d.x), static_cast<float>(d.y) } );
}

const sf::Vector2f& AABB::getPos() const { return this->rect.getPosition(); }

const sf::IntRect& AABB::getBox() const { return this->cbox; }

const sf::RectangleShape AABB::getRect() const { return this->rect; }
