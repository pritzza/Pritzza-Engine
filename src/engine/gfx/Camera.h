#pragma once

#include <SFML/Graphics.hpp>

class Sprite;

class Camera
{
private:
	const unsigned int WINDOW_WIDTH;
	const unsigned int WINDOW_HEIGHT;

private:
	sf::View view;

	sf::Vector2f pos{};
	float zoom{ 1.f };

	// idea: add pointer to game object and camera speed so you can just give the camera something to point at

public:
	Camera(const unsigned int WINDOW_WIDTH, const unsigned int WINDOW_HEIGHT);

	void update();

	const bool isInView(const Sprite& s) const;

	void move(const sf::Vector2f& vel);		// relative
	void setPos(const sf::Vector2f& pos);	// absolute

	void addZoom(const float addend);
	void multiplyZoom(const float factor);
	void setZoom(const float zoom);

	const sf::Vector2f& getPos() const;
	const sf::View& getView() const;
	const float getZoom() const;
};