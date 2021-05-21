#include "GameState.h"

#include "../util/GameData.h"

#include <cmath>

#include <iostream>

void GameState::load()
{
	// load all resources

	//buffer.create(data.window.getWidth(), data.window.getHeight());

	//// LOADING RESOURCES

	// LOADING TEXTURES
	auto& tm = data.resourceManagers.textureManager;
	
	const auto& tileTexture = tm.get(tm.load(TEXTURE::TILES_ISOMETRIC));
	const auto& frogTexture = tm.get(tm.load(TEXTURE::FROG_SPRITE_SHEET));
	const auto& snailTexture = tm.get(tm.load(TEXTURE::SNAIL_SPRITE_SHEET));
	
	// LOADING AUDIO

	//auto& am = data.resourceManagers.audioManager;

	//const auto& bgmAudio = am.get(am.load(AUDIO::RATS_IN_WATER_SONG));

	// INITIALIZEING MAP
	constexpr int LEVEL_WIDTH{ 200 };
	constexpr int LEVEL_HEIGHT{ 200 };

	tileMap.init({ LEVEL_WIDTH, LEVEL_HEIGHT }, tileTexture);
	
	// INITIALIZING ENTITIES
	//           pos       dime      texture             shDime  keyFrameDur
	e1->init( { 64,64 }, { 16,16 }, snailTexture,		{ 4,8 }, .2f );
	e2->init( { 64,64 }, { 16,16 }, frogTexture,		{ 4,8 }, .1f );
	
	entities.push_back(e1);
	entities.push_back(e2);
	
	// INITIALIZING CAMERA

	Camera& c{ data.camera };

	c.setPos(e1->getCenterPos());
	c.setFollowingTarget(*e1);
	c.startFollowing();

	//data.camera.setPos({ 74, 49 });

	// INITIALIZING AUDIO

	//bgm.setBuffer(bgmAudio);
	//bgm.play();

	// FINISHING
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
		// pan linearly
		//camera.startPanning( e2->getCenterPos(), 100.f, PanningType::LINEAR);

		if (isZoomedIn)
		{
			camera.setZoom(1);
			isZoomedIn = false;
		}
		else
		{
			camera.setZoom(4);
			isZoomedIn = true;
		}
	}
	if (kb.e.isTapped() && !camera.isPanComplete())
	{
		// pan exponentially
		//camera.startPanning(e2->getCenterPos(), 0.5f, PanningType::EXPONENTIAL);

		tileMap.init({ 100, 100 }, data.resourceManagers.textureManager.get(TEXTURE::TILES_ISOMETRIC));
	}
	else if ((kb.space.isTapped() || kb.e.isTapped()) && camera.isPanComplete())
	{
		// reset camera back to e1
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
	
	for (const auto& e : entities)
		w.draw(*e, true);

	//w.draw(s);

	w.endDraw();
}
