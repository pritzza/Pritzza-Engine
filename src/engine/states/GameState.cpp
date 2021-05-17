#include "GameState.h"

#include "../util/GameData.h"

#include <cmath>

#include <iostream>

void GameState::load()
{
	// load all resources

	//buffer.create(data.window.getWidth(), data.window.getHeight());

	auto& tm = data.resourceManagers.textureManager;
	
	const auto& tileTexture = tm.get(tm.load(TEXTURE::TILES));
	const auto& frogTexture = tm.get(tm.load(TEXTURE::FROG_SPRITE_SHEET));
	
	tileMap.init({ 100, 100 }, tileTexture);
	
	//           pos       dime      texture             shDime  keyFrameDur
	e1->init( { 64,64 }, { 16,16 }, frogTexture,		{ 4,8 }, .1f );
	e2->init( { 64,64 }, { 16,16 }, frogTexture,		{ 4,8 }, .1f );
	
	entities.push_back(e1);
	entities.push_back(e2);
	
	data.camera.setPos(e1->getCenterPos());
	
	data.camera.setFollowingTarget(*e1);
	data.camera.startFollowing();
	
	//data.camera.setZoom(.5f);

	//data.camera.setPos({ 74, 49 });

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
	
	Camera& camera{ data.camera };
	
	if (kb.space.isTapped() && !camera.isPanComplete())
	{
		camera.startPanning( e2->getCenterPos(), 100.f, PanningType::LINEAR);
	}
	if (kb.e.isTapped() && !camera.isPanComplete())
	{
		camera.startPanning(e2->getCenterPos(), 0.5f, PanningType::EXPONENTIAL);
	}
	else if ((kb.space.isTapped() || kb.e.isTapped()) && camera.isPanComplete())
	{
		camera.setPos(e1->getCenterPos());
		camera.startFollowing();
	}
}

void GameState::update(const float dt)
{
	// tick everything

	// cellular automata stuff
	//if (p < (data.window.getWidth() * data.window.getHeight()) - 1)
	//{
	//	++p;
	//	buffer.setPixel(p % data.window.getWidth(), p / data.window.getWidth(), 
	//		sf::Color( int(cos(p) * 8960) % 255, int(tan(p) * 379) % 255, int(sin(p) * 2006) % 255
	//	));
	//}
	//
	//t.loadFromImage(buffer);
	//s.setTexture(t);

	this->time += dt;// *3.f;

	e2->move({ cosf(time * 2) / 5.f, sinf(time * 2) / 5.f });

	for (const auto e : entities)
		e->update(dt);
	
	//std::cout << e1->getVel().x << ", " << e1->getVel().y << '\n';
	
	if (e1->isColliding(*e2))
	{
		//std::shared_ptr<Entity> e = std::make_shared<Entity>();
		//auto& tm = data.resourceManagers.textureManager;
		//
		//e->init({ entities.back()->getCenterPos().x,0 }, {4,4}, tm.get(TEXTURE::DEFAULT));
		//
		//entities.push_back(e);
	
		//data.camera.startPanning({ 100.f, 0.f }, 1.f, PanningType::LINEAR);
		
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

	//w.draw(s);

	w.endDraw();
}
