#include "Camera.h"

#include "../gfx/Sprite.h"
#include "../game objects/Entity.h"

#include <iostream>

#include <cmath>

Camera::Camera(const unsigned int WINDOW_WIDTH, const unsigned int WINDOW_HEIGHT)
	:
	WINDOW_WIDTH{ WINDOW_WIDTH },
	WINDOW_HEIGHT{ WINDOW_HEIGHT }
{}

void Camera::update(const float dt)
{
	//std::cout << "(" << pos.x << ", " << pos.y << ") zoom: " << zoom << '\n';

	this->updatePos(dt);

	this->view.setSize(WINDOW_WIDTH / zoom, WINDOW_HEIGHT / zoom);
}

void Camera::updatePos(const float dt)
{
	switch (this->activeState)
	{
	case CameraState::FOLLOWING:			this->follow(dt);	break;
	case CameraState::PANNING_LINEAR:		this->pan(true);	break;
	case CameraState::PANNING_EXPONENTIAL:	this->pan(false);	break;
	case CameraState::STATIC: break;	/*if the camera is static, do nothing*/
	}

	constexpr bool ROUND_CAMERA_POS{ false };

	if (ROUND_CAMERA_POS)
		this->view.setCenter(static_cast<int>(pos.x), static_cast<int>(pos.y));
	else
		this->view.setCenter(pos.x, pos.y);
}

void Camera::pan(const bool isLinear)
{
	const sf::Vector2f distance{ panPoint.x - pos.x, panPoint.y - pos.y };
	sf::Vector2f vel;

	if (isLinear)	// linear pan
	{	
		const float angle{ atan(distance.y / distance.x) };

		vel = { angle / panningSpeed, angle / panningSpeed };
	}
	else // exponential pan	
		vel = { distance.x / panningSpeed, distance.y / panningSpeed };

	this->move(vel);

	// if linear and panPoint vel * threshold close enough
	// vs if exponential and within 1 * threshold distance of being close enough to panPoint
	if  ( (abs(distance.x) + abs(distance.y) < vel.x * PANNING_DISTANCE_THRESHOLD   ||	
		( (abs(distance.x) + abs(distance.y) < 1.f   * PANNING_DISTANCE_THRESHOLD)) && !isLinear))
	{
		this->setPos(this->target->getCenterPos());
		this->setState(defaultState);
	}

	//std::cout << "panning...\n";
}

void Camera::follow(const float dt)
{
	this->move({ target->getVel().x * dt, target->getVel().y * dt });
	//std::cout << "following...\n";
}

const bool Camera::isInView(const Sprite& s) const
{
	const float sx{ s.getPos().x };
	const float sy{ s.getPos().y };
	const int	sw{ s.getDimensions().x };
	const int	sh{ s.getDimensions().y };

	const float x{ pos.x - (WINDOW_WIDTH / zoom / 2.f) };
	const float y{ pos.y - (WINDOW_HEIGHT / zoom / 2.f) };
	const float w{ WINDOW_WIDTH / zoom };
	const float h{ WINDOW_HEIGHT / zoom };

	return
		(sx + sw > x && sx < x + w) &&
		(sy + sh > y && sy < y + h);
}

void Camera::panTo(const sf::Vector2f& pos, const float smoothness)
{
	this->panningSpeed = smoothness;
	this->panPoint = pos;
}

void Camera::setState(const CameraState s)		{ this->activeState = s; }
void Camera::setFollowingTarget(const Entity& target)	  { this->target = &target;	}

void Camera::addZoom(const float addend)		{ this->zoom += addend; }
void Camera::multiplyZoom(const float factor)	{ this->zoom *= factor; }
void Camera::setZoom(const float zoom)			{ this->zoom = zoom;	}

void Camera::move(const sf::Vector2f& vel)		{ this->pos.x += vel.x;	this->pos.y += vel.y; }
void Camera::setPos(const sf::Vector2f& pos)	{ this->pos.x = pos.x;	this->pos.y = pos.y;  }

const sf::Vector2f& Camera::getPos() const	{ return this->pos;	 }
const sf::View& Camera::getView() const		{ return this->view; }
const float Camera::getZoom() const			{ return this->zoom; }
