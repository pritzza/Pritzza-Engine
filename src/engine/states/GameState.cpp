#include "GameState.h"

#include "../util/GameData.h"

#include <cmath>

#include <iostream>

void GameState::load()
{
	// load all resources

	//// LOADING RESOURCES

	// LOADING TEXTURES
	auto& tm = data.resourceManagers.textureManager;
	
	const auto& tileTexture = tm.get(tm.load(TEXTURE::TILES_ISOMETRIC));
	const auto& frogTexture = tm.get(tm.load(TEXTURE::FROG_SPRITE_SHEET));
	const auto& snailTexture = tm.get(tm.load(TEXTURE::SNAIL_SPRITE_SHEET));
	
	// LOADING AUDIO

	//auto& am = data.resourceManagers.audioManager;

	//const auto& bgmAudio = am.get(am.load(AUDIO::RATS_IN_WATER_SONG));

	// LOAD TEXT

	auto& fm = data.resourceManagers.fontManager;

	const auto& defaultFont = fm.get(FONT::ERROR);

	//			  font			text		 pos
	text.init( defaultFont, "this is text", {0,0}, 100 );

	// INITIALIZEING MAP
	tileMap.init({ LEVEL_WIDTH, LEVEL_HEIGHT }, tileTexture);

	tileMap.setTarget(*e1);

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

	// INITIALIZING AUDIO

	// FINISHING
	setLoaded();	// enable the state's "loaded" flag after everything has been loaded
}

void GameState::unload()
{
	// release all resources
	// textures
	auto& tm = data.resourceManagers.textureManager;

	tm.unload(TEXTURE::TILES_ISOMETRIC);
	tm.unload(TEXTURE::FROG_SPRITE_SHEET);
	tm.unload(TEXTURE::SNAIL_SPRITE_SHEET);

	// fonts
	auto& fm = data.resourceManagers.fontManager;

	//fm.unload(FONT::);

	// audio
	//auto& am = data.resourceManagers.audioManager;

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
	
	if (kb.space.isTapped())
	{
		camera.stopPanning();
		camera.startFollowing();

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
	if (kb.e.isTapped())
	{
		tileMap.init({ LEVEL_WIDTH, LEVEL_HEIGHT }, data.resourceManagers.textureManager.get(TEXTURE::TILES_ISOMETRIC));
	}
}

void GameState::update(const double dt, const double pt)
{
	this->time += dt;

	e2->move({ cosf(time * 2) / 5.f, sinf(time * 2) / 5.f });

	for (const auto e : entities)
		e->update(dt);
	
	//if (e1->isColliding(*e2))
	//{
	//	std::shared_ptr<Entity> e = std::make_shared<Entity>();
	//	auto& tm = data.resourceManagers.textureManager;
	//	
	//	e->init({ entities.back()->getCenterPos().x,0 }, {4,4}, tm.get(TEXTURE::DEFAULT));
	//	
	//	entities.push_back(e);
	//
	//	data.camera.startPanning({ 100.f, 0.f }, 1.f, PanningType::LINEAR);
	//	
	//	e1->move({ 1,0 });
	//	e1->setSize({ 32,32 });
	//	
	//	data.camera.multiplyZoom(1.01f);
	//}

	// if you want the weird "load in" effect
	//tileMap.update();

	text.setText(std::to_string(pt));
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

	//w.draw(text);

	w.endDraw();
}
