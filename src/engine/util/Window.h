#pragma once

#include <SFML/Graphics.hpp>

class Camera;
class Sprite;
class Entity;
class Text;
class TileMap;

class Window
{
private:
	sf::RenderWindow renderWindow;

	const Camera& camera;

	bool focused{ true };

	const unsigned int WIDTH;
	const unsigned int HEIGHT;
	const unsigned int PIXEL_SIZE;

	int renderCount{};
	int totalCount{};

public:
	Window(const Camera& camera, const std::string& windowName, const unsigned int width, const unsigned int height, const unsigned int size);

	void update();

	void beginDraw();
	void endDraw();
	void draw(const Sprite& sprite);
	void draw(Entity& entity, const bool drawBounds = false);
	void draw(const Text& text);

	sf::RenderWindow& getWindow();

	const bool isOpen() const;
	const bool isFocused() const;

	const unsigned int getWidth() const;
	const unsigned int getHeight() const;
	const unsigned int getPixelSize() const;
};