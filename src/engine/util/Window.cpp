#include "Window.h"

#include "../gfx/Camera.h"
#include "../gfx/Sprite.h"
#include "../game objects/Entity.h"

Window::Window(const Camera& camera, const std::string& windowName, const unsigned int width, const unsigned int height, const unsigned int size)
	:
	window(sf::VideoMode(width * size, height * size), windowName),
	camera{ camera },
	WIDTH{ width },
	HEIGHT{ height },
	PIXEL_SIZE{ size }
{}

void Window::update()
{
	this->window.setView(camera.getView());

	sf::Event event;

	if (this->window.pollEvent(event))
		switch (event.type)
		{
		case sf::Event::Closed:			this->window.close();			break;
		case sf::Event::GainedFocus:	this->focused = true;	break;
		case sf::Event::LostFocus:		this->focused = false;	break;
		}
}

void Window::beginDraw()
{
	this->window.clear(sf::Color(1, 69, 13));
}

void Window::endDraw()
{
	this->window.display();
}

void Window::draw(const Sprite& sprite)
{
	if (camera.isInView(sprite))
		this->window.draw(sprite.getSprite());
}

void Window::draw(Entity& entity, const bool drawBounds)
{
	if (camera.isInView(entity.getSprite()))
	{
		this->window.draw(entity.getSFSprite());

		if (drawBounds)
			this->window.draw(entity.getRect());
	}
}

sf::RenderWindow& Window::getWindow() { return this->window;	}

const bool Window::isOpen() const	  { return window.isOpen(); }
const bool Window::isFocused() const  { return this->focused;   }

const unsigned int Window::getWidth()  const		{ return WIDTH;		  }
const unsigned int Window::getHeight() const		{ return HEIGHT;	  }
const unsigned int Window::getPixelSize()  const	{ return PIXEL_SIZE;  }
