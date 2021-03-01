#include "Camera.h"

#include <iostream>

Camera::Camera(const unsigned int WINDOW_WIDTH, const unsigned int WINDOW_HEIGHT)
	:
	WINDOW_WIDTH { WINDOW_WIDTH },
	WINDOW_HEIGHT { WINDOW_HEIGHT }
{}

void Camera::update()
{
	this->view.setCenter(pos.x + WINDOW_WIDTH/2, pos.y + WINDOW_HEIGHT/2);

	this->view.setSize(WINDOW_WIDTH / zoom, WINDOW_HEIGHT / zoom);
}

void Camera::addZoom(const float addend)		{ this->zoom += addend; }
void Camera::multiplyZoom(const float factor)	{ this->zoom *= factor; }
void Camera::setZoom(const float zoom)			{ this->zoom  = zoom;   }

void Camera::move(const sf::Vector2i& vel)		{ this->pos += vel;  }
void Camera::setPos(const sf::Vector2i& pos)	{ this->pos = pos;	 }

const sf::Vector2i& Camera::getPos() const		{ return this->pos;	 }
const sf::View& Camera::getView() const			{ return this->view; }