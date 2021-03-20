#include "GameState.h"

#include "../util/GameData.h"

#include <iostream>

void GameState::load()
{
	// load all resources

	auto& tm = data.resourceManagers.textureManager;

	const auto& t = tm.get(tm.load(TEXTURE::DEFAULT));

	tileMap.init({ 100, 100 }, tm);

	e1.init( { 0,0 }, {16,16} );
	e2.init( { 0,0 }, {12,12} );

	e1.setTexture(t);
	e2.setTexture(t);

	entities.push_back(&e1);
	entities.push_back(&e2);

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
		e1.move({ 0, -1 });
	if (kb.a.isTapped() || kb.a.isHeld())
		e1.move({ -1, 0 });
	if (kb.s.isTapped() || kb.s.isHeld())
		e1.move({ 0, 1 });
	if (kb.d.isTapped() || kb.d.isHeld())
		e1.move({ 1, 0 });
}

void GameState::update(const float dt)
{
	// tick everything

	data.camera.setPos(e1.getCenterPos());

	for (const auto e : entities)
		e->update(dt);

	if (e1.isColliding(e2))
	{
		e1.move({ 1,0 });
		e1.setSize({ 32,32 });
	}

	//data.camera.multiplyZoom(1.01f);
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
