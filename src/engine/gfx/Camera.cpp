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

/*************************/
/*    PRIVATE METHODS    */
/*************************/

void Camera::update(const float dt)
{
	//std::cout << "(" << pos.x << " + " << vel.x << ", " << pos.y << " + " << vel.y << ") zoom: " << zoom << '\n';

	if (this->tempZoom != this->NULL_ZOOM_VALUE)
	{
		this->zoom = tempZoom;
		tempZoom = this->NULL_ZOOM_VALUE;
	}

	this->updatePos(dt);

	this->view.setSize(WINDOW_WIDTH / zoom, WINDOW_HEIGHT / zoom);
}

void Camera::updatePos(const float dt)
{
	switch (this->activeState)
	{
	case CameraState::FOLLOWING: this->follow();	break;
	case CameraState::PANNING:	 this->pan(dt);		break;
	}

	if (ROUND_CAMERA_POS)
		this->view.setCenter(static_cast<int>(pos.x), static_cast<int>(pos.y));
	else
		this->view.setCenter(pos.x, pos.y);
}

void Camera::pan(const float dt)
{
	/* Thanks DeKrain for helping me with linear panning */

	// Ideally this should be done once and then result saved
	const sf::Vector2f displacement{ focusPoint.x - pos.x, focusPoint.y - pos.y };

	const float distance = std::hypot(displacement.x, displacement.y); // Hehe, shortcut for sqrt(displacement.x * displacement.x + displacement.y * displacement.y)

	if (!this->panComplete)
	{
		if (this->panningType == PanningType::LINEAR)
			this->vel = displacement * (panningSpeed / distance);
		else if (this->panningType == PanningType::EXPONENTIAL)
			this->vel = displacement / panningSpeed;

		this->vel *= dt;

		this->pos += this->vel;
	}

	if (nearingFocusPoint() && this->panningType == PanningType::EXPONENTIAL)
	{
		this->panComplete = true;
	}
	else if (passingFocusPoint())
	{
		this->panComplete = true;
		this->setPos(focusPoint);
		this->vel = { 0,0 };
	}

	//std::cout << "panning...\n";
}

void Camera::follow()
{
	if (this->target != nullptr)
		this->pos = this->target->getCenterPos();
	
	//std::cout << "following...\n";
}

const bool Camera::passingFocusPoint() const
{
	return ((startingPoint.x < focusPoint.x && (pos + vel).x >= focusPoint.x) || (startingPoint.x > focusPoint.x && (pos + vel).x <= focusPoint.x)) &&
		   ((startingPoint.y < focusPoint.y && (pos + vel).y >= focusPoint.y) || (startingPoint.y > focusPoint.y && (pos + vel).y <= focusPoint.y));
}

const bool Camera::nearingFocusPoint() const
{
	return (abs(focusPoint.x - pos.x) + abs(focusPoint.y - pos.y) < PANNING_DISTANCE_THRESHOLD);
}

/*************************/
/*    PUBLIC* METHODS    */
/*************************/

void Camera::startPanning(const sf::Vector2f& pos, const float smoothness, const PanningType pt)
{
	this->panComplete = false;
	this->activeState = CameraState::PANNING;
	this->panningType = pt;
	this->panningSpeed = smoothness;

	this->startingPoint = this->pos;
	this->focusPoint = pos;
}

void Camera::setFollowingTarget(const Entity& target) { this->target = &target; }
void Camera::startFollowing()
{
	this->activeState = CameraState::FOLLOWING;
	this->panComplete = false;
}

const bool Camera::isInView(const Sprite& s) const
{
	// dimensions of sprite
	const float sx{ s.getPos().x };
	const float sy{ s.getPos().y };
	const int	sw{ s.getDimensions().x };
	const int	sh{ s.getDimensions().y };

	// dimensions of this camera
	const float x{ pos.x - (WINDOW_WIDTH / zoom / 2.f) };
	const float y{ pos.y - (WINDOW_HEIGHT / zoom / 2.f) };
	const float w{ WINDOW_WIDTH / zoom };
	const float h{ WINDOW_HEIGHT / zoom };

	return
		((sx + sw >= x && sx <= x + w) &&
		 (sy + sh >= y && sy <= y + h)) ||
		((sx <= x && sx + sw >= x + w) &&
		 (sy <= y && sy + sh >= y + h));
}

void Camera::addZoom(const float addend)		{ this->zoom += addend; }
void Camera::multiplyZoom(const float factor)	{ this->zoom *= factor; }
void Camera::setZoom(const float zoom) { this->tempZoom = zoom;	std::cout << "SET ZOOM\n\n"; }

void Camera::move(const sf::Vector2f& vel)		{ this->vel.x = vel.x;	this->vel.y = vel.y; }
void Camera::setPos(const sf::Vector2f& pos)	{ this->pos.x = pos.x;	this->pos.y = pos.y; }

const sf::Vector2f& Camera::getPos() const	{ return this->pos;	 }
const sf::View& Camera::getView() const		{ return this->view; }
const float Camera::getZoom() const			{ return this->zoom; }

const bool Camera::isPanComplete() const    { return this->panComplete; }
