#include "GameState.h"

#include "../util/GameData.h"

#include <cmath>

#include <iostream>

void GameState::load()
{
	// load all resources

	auto& tm = data.resourceManagers.textureManager;

	const auto& t = tm.get(tm.load(TEXTURE::DEFAULT));

	tileMap.init({ 100, 100 }, tm);

	e1->init( { 64,64 }, {16,16}, t );
	e2->init( { 0,0 }, {12,12}, t );

	entities.push_back(e1);
	entities.push_back(e2);

	data.camera.setPos(e1->getCenterPos());

	data.camera.setFollowingTarget(*e1);
	data.camera.setState(CameraState::FOLLOWING);

	//data.camera.setZoom(.5f);

	setLoaded();	// enable the state's "loaded" flag after everything has been loaded
}

void GameState::unload()
{
	// release all resources

	data.resourceManagers.textureManager.unload(TEXTURE::DEFAULT);
}

void GameState::handleInput()
{
	// listen to any keyboard and mouse input to do stuff
	
	Keyboard& kb{ data.keyboard };

	if (kb.w.isTapped() || kb.w.isHeld())
		e1->move({ 0, -1 });
	if (kb.a.isTapped() || kb.a.isHeld())
		e1->move({ -1, 0 });
	if (kb.s.isTapped() || kb.s.isHeld())
		e1->move({ 0, 1 });
	if (kb.d.isTapped() || kb.d.isHeld())
		e1->move({ 1, 0 });

	if (kb.space.isTapped())
	{
		data.camera.setState(CameraState::PANNING_EXPONENTIAL);
		data.camera.panTo({ 0,0 }, 5.f);
	}
	else if (kb.space.isReleased())
		data.camera.setState(CameraState::FOLLOWING);
}

void GameState::update(const float dt)
{
	// tick everything

	for (const auto e : entities)
		e->update(dt);

	//std::cout << e1->getPos().x << ", " << e1->getPos().y << '\n';

	if (e1->isColliding(*e2))
	{
		std::shared_ptr<Entity> e = std::make_shared<Entity>();
		auto& tm = data.resourceManagers.textureManager;

		e->init({ entities.back()->getCenterPos().x,0 }, {4,4}, tm.get(TEXTURE::DEFAULT));

		entities.push_back(e);

		//data.camera.panTo({ 369.f, 369.f }, 1.f);
		//data.camera.setState(CameraState::PANNING_LINEAR);
		//
		//e1->move({ 1,0 });
		//e1->setSize({ 32,32 });
		//
		//data.camera.multiplyZoom(1.01f);
	}
}

void GameState::render() const
{
	// render scene objects and entities and stuff here
	
	Window& w{ data.window };

	w.beginDraw();

	for (const auto& t : tileMap.getTiles())
		w.draw(t.getSprite());

	for (const auto e : entities)
		w.draw(*e, true);

	w.endDraw();
}
