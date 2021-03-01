#pragma once

#include <SFML/Graphics.hpp>

class Camera;

class Window
{
private:
	sf::RenderWindow window;

	const Camera& camera;

	bool focused{ true };

	const unsigned int WIDTH;
	const unsigned int HEIGHT;
	const unsigned int PIXEL_SIZE;

public:
	Window(const Camera& camera, const std::string& windowName, const unsigned int width, const unsigned int height, const unsigned int size);

	void update();

	void beginDraw();
	void endDraw();
	void draw(const sf::Drawable& drawable);

	sf::RenderWindow& getWindow();

	const bool isOpen() const;
	const bool isFocused() const;

	const unsigned int getWidth() const;
	const unsigned int getHeight() const;
	const unsigned int getPixelSize() const;
};