#pragma once

#include <SFML/Graphics.hpp>

class Sprite;
class Entity;
class GameObject;

enum class CameraState 
{
	FOLLOWING,
	PANNING,
	STATIC
};

enum class PanningType
{
	LINEAR,
	EXPONENTIAL
};

class Camera
{
private:
	const unsigned int WINDOW_WIDTH;
	const unsigned int WINDOW_HEIGHT;
	static constexpr bool ROUND_CAMERA_POS{ false };
	static constexpr float PANNING_DISTANCE_THRESHOLD{ 1.f };
	static constexpr float MIN_VEL{ 0.1f };

private:
	sf::View view;

	sf::Vector2f pos{};
	sf::Vector2f vel{};
	float zoom{ 1.f };

	const float NULL_ZOOM_VALUE{ -1.f };	// arbitrary value to say there isnt any tempZoom value we need to assign to zoom
	float tempZoom{ this->NULL_ZOOM_VALUE };

	CameraState activeState{ CameraState::STATIC };
	CameraState defaultState{ CameraState::FOLLOWING };

	// following
	const Entity* target{ nullptr };

	// panning
	sf::Vector2f focusPoint{};
	sf::Vector2f startingPoint{};
	float panningSpeed{ 1.f };
	
	bool panComplete{ false };
	PanningType panningType{ PanningType::LINEAR };

private:
	void updatePos(const float dt);
	void pan(const float dt);
	void follow();

	// used to see determine when to stop camera pan
	const bool passingFocusPoint() const; // if camera has passed focus point when panning linearly
	const bool nearingFocusPoint() const; // if camera has gotten close enough to focus point when panning exponentially

public:
	Camera(const unsigned int WINDOW_WIDTH, const unsigned int WINDOW_HEIGHT);

	void update(const float dt);

	// having the camera follow things
	void setFollowingTarget(const Entity& target);
	void startFollowing();

	void startPanning(const sf::Vector2f& pos, const float smoof, const PanningType pt);	// smooth is how long it takes to pan

	const bool isInView(const Sprite& s) const;

	// moving the camera's view
	void move(const sf::Vector2f& vel);		// relative
	void setPos(const sf::Vector2f& pos);	// absolute

	// modifiying the zoom of the camera
	void addZoom(const float addend);
	void multiplyZoom(const float factor);
	void setZoom(const float zoom);

	// getters
	const sf::Vector2f& getPos() const;
	const sf::View& getView() const;
	const float getZoom() const;

	const bool isPanComplete() const;
};