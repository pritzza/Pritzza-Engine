#include "Camera.h"

#include "../gfx/Sprite.h"

#include <iostream>

Camera::Camera(const unsigned int WINDOW_WIDTH, const unsigned int WINDOW_HEIGHT)
	:
	WINDOW_WIDTH{ WINDOW_WIDTH },
	WINDOW_HEIGHT{ WINDOW_HEIGHT }
{}

void Camera::update()
{
	constexpr bool ROUND_CAMERA_POS{ false };

	//std::cout << "x: " << pos.x << ", " << pos.y << " / " << zoom << '\n';

	if (ROUND_CAMERA_POS)
		this->view.setCenter(static_cast<int>(pos.x), static_cast<int>(pos.y));
	else
		this->view.setCenter(pos.x, pos.y);

	this->view.setSize(WINDOW_WIDTH / zoom, WINDOW_HEIGHT / zoom);
}

const bool Camera::isInView(const Sprite& s) const
{
	const float sx{ s.getPos().x };
	const float sy{ s.getPos().y };
	const int	sw{ s.getDimensions().x };
	const int	sh{ s.getDimensions().y };

	const float x{ pos.x - (WINDOW_WIDTH  / zoom  / 2.f) };
	const float y{ pos.y - (WINDOW_HEIGHT / zoom  / 2.f) };
	const float w{ WINDOW_WIDTH  / zoom };
	const float h{ WINDOW_HEIGHT / zoom };

	return 
		(sx + sw > x && sx < x + w) &&
		(sy + sh > y && sy < y + h);
}

void Camera::addZoom(const float addend) { this->zoom += addend; }
void Camera::multiplyZoom(const float factor) { this->zoom *= factor; }
void Camera::setZoom(const float zoom) { this->zoom = zoom; }

void Camera::move(const sf::Vector2f& vel) { this->pos.x += vel.x / 100.f;   this->pos.y += vel.y / 100.f; }
void Camera::setPos(const sf::Vector2f& pos) { this->pos.x = pos.x;			this->pos.y = pos.y; }

const sf::Vector2f& Camera::getPos() const { return this->pos; }
const sf::View& Camera::getView() const { return this->view; }

const float Camera::getZoom() const { return this->zoom; }
