#include "GameObject.h"

void GameObject::init(const sf::Vector2f& pos, const sf::Vector2u& dimensions)
{
	this->pos = pos;

	this->setSize(dimensions);
}

void GameObject::init(const sf::Vector2f& pos, const sf::Vector2u& dimensions, const sf::Texture& t)
{
	this->pos = pos;

	this->setSize(dimensions);
	this->setTexture(t);
}

void GameObject::update(const float dt)
{
	this->box.update(this->pos);
	this->sprite.update(this->pos);
}

const bool GameObject::isColliding(const GameObject& e) const
{
	return this->box.isColliding(e.getAABB());
}

void GameObject::setSize(const sf::Vector2u& d)
{
	this->box.setDimensions(d);
	this->sprite.setDimensions(d);
}

void GameObject::setTexture(const sf::Texture& texture)	 { this->sprite.setTexture(texture); }

void GameObject::setPos(const sf::Vector2f pos)			 { this->pos = pos;					 }


const sf::Vector2f& GameObject::getPos() const			 { return this->box.getPos();		 }
const sf::Vector2f  GameObject::getCenterPos() const	 
{ 
	return sf::Vector2f( 
	this->pos.x + this->sprite.getDimensions().x / 2.f, 
	this->pos.y + this->sprite.getDimensions().y / 2.f
	);	
}

Sprite& GameObject::getSprite()							 { return this->sprite;				 }
const Sprite& GameObject::getSprite() const				 { return this->sprite;				 }
const sf::Sprite& GameObject::getSFSprite()	const		 { return this->sprite.getSprite();	 }

const AABB& GameObject::getAABB() const					 { return this->box;			 	 }
const sf::RectangleShape GameObject::getRect() const	 { return this->box.getRect();		 }
