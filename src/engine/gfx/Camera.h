#pragma once

#include <SFML/Graphics.hpp>

class Sprite;
class Entity;
class GameObject;

enum class CameraState 
{
	FOLLOWING,
	PANNING_LINEAR,
	PANNING_EXPONENTIAL,
	STATIC
};

class Camera
{
private:
	const unsigned int WINDOW_WIDTH;
	const unsigned int WINDOW_HEIGHT;

private:
	sf::View view;

	sf::Vector2f pos{};
	float zoom{ 1.f };

	CameraState activeState{ CameraState::STATIC };
	CameraState defaultState{ CameraState::FOLLOWING };

	// following
	const Entity* target{ nullptr };

	// panning
	sf::Vector2f panPoint{ 0.f, 0.f };
	float panningSpeed{ 1.f };
	static constexpr float PANNING_DISTANCE_THRESHOLD{ 5.f };

private:
	void updatePos(const float dt);
	void pan(const bool isLinear);
	void follow(const float dt);

public:
	Camera(const unsigned int WINDOW_WIDTH, const unsigned int WINDOW_HEIGHT);

	void update(const float dt);

	const bool isInView(const Sprite& s) const;

	void setState(const CameraState s);

	// moving the camera's view
	void move(const sf::Vector2f& vel);		// relative
	void setPos(const sf::Vector2f& pos);	// absolute
	void panTo(const sf::Vector2f& pos, const float smoof);	// smoof is how long the pan takes

	// modifiying the zoom of the camera
	void addZoom(const float addend);
	void multiplyZoom(const float factor);
	void setZoom(const float zoom);

	// having the camera follow things
	void setFollowingTarget(const Entity& target);

	// getters
	const sf::Vector2f& getPos() const;
	const sf::View& getView() const;
	const float getZoom() const;
};