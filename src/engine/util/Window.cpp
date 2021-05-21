#include "Window.h"

#include "../gfx/Camera.h"
#include "../gfx/Sprite.h"
#include "../game objects/Entity.h"

Window::Window(const Camera& camera, const std::string& renderWindowName, const unsigned int width, const unsigned int height, const unsigned int size)
	:
	renderWindow(sf::VideoMode(width * size, height * size), renderWindowName),
	camera{ camera },
	WIDTH{ width },
	HEIGHT{ height },
	PIXEL_SIZE{ size }
{}

void Window::update()
{
	this->renderWindow.setView(camera.getView());

	sf::Event event;

	if (this->renderWindow.pollEvent(event))
		switch (event.type)
		{
		case sf::Event::Closed:			this->renderWindow.close();			break;
		case sf::Event::GainedFocus:	this->focused = true;	break;
		case sf::Event::LostFocus:		this->focused = false;	break;
		}
}

void Window::beginDraw()
{
	this->renderWindow.clear(sf::Color(1, 69, 13));
}

void Window::endDraw()
{
	this->renderWindow.display();
}

void Window::draw(const Sprite& sprite)
{
	if (camera.isInView(sprite))
	{
		this->renderWindow.draw(sprite.getSprite());
	}
	}

void Window::draw(Entity& entity, const bool drawBounds)
{
	if (camera.isInView(entity.getSprite()))
	{
		this->renderWindow.draw(entity.getSFSprite());

		if (drawBounds)
			this->renderWindow.draw(entity.getRect());
	}
}

sf::RenderWindow& Window::getWindow() { return this->renderWindow;	}

const bool Window::isOpen() const	  { return renderWindow.isOpen(); }
const bool Window::isFocused() const  { return this->focused;   }

const unsigned int Window::getWidth()  const		{ return WIDTH;		  }
const unsigned int Window::getHeight() const		{ return HEIGHT;	  }
const unsigned int Window::getPixelSize()  const	{ return PIXEL_SIZE;  }
