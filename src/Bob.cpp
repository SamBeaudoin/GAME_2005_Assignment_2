#include "Bob.h"
#include "TextureManager.h"

Bob::Bob()
{
	TextureManager::Instance().load("../Assets/textures/sled.png", "ship");

	auto size = TextureManager::Instance().getTextureSize("ship");
	setWidth(size.x);
	setHeight(size.y);
}

Bob::~Bob()
= default;

void Bob::draw()
{
	TextureManager::Instance().draw("ship", getTransform()->position.x, getTransform()->position.y, 0, 255, true);
}

void Bob::update()
{
}

void Bob::clean()
{
}

