#pragma once

#include <SFML/Graphics.hpp>

class Camera
{
private:
	sf::View view;

	sf::Vector2i pos{};
	float zoom{1.f};

	const unsigned int WINDOW_WIDTH;
	const unsigned int WINDOW_HEIGHT;

public:
	Camera(const unsigned int WINDOW_WIDTH, const unsigned int WINDOW_HEIGHT);

	void update();

	void move(const sf::Vector2i& vel);		// relative
	void setPos(const sf::Vector2i& pos);	// absolute

	void addZoom(const float addend);
	void multiplyZoom(const float factor);
	void setZoom(const float zoom);

	const sf::Vector2i& getPos() const;
	const sf::View& getView() const;
	const float getZoom() const;
};