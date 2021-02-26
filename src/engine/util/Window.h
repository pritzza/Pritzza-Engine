#pragma once

#include <SFML/Graphics.hpp>

class Window
{
private:
	sf::RenderWindow window;

	bool focused{ true };

	const unsigned int WIDTH;
	const unsigned int HEIGHT;
	const unsigned int SCALE;

public:
	Window(const std::string& windowName, const unsigned int w, const unsigned int h, const unsigned int s);

	void update();

	void beginDraw();
	void endDraw();
	void draw(const sf::Drawable& drawable);

	sf::RenderWindow& getWindow();

	const bool isOpen() const;
	const bool isFocused() const;

	const unsigned int width() const;
	const unsigned int height() const;
	const unsigned int scale() const;
};