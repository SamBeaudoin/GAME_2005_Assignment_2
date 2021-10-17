#include "Background.h"
#include "TextureManager.h"

Background::Background()
{
	TextureManager::Instance().load("../Assets/textures/sky1.png", "sky");

	auto size = TextureManager::Instance().getTextureSize("sky");
	setWidth(size.x);
	setHeight(size.y);
}

Background::~Background()
= default;

void Background::draw()
{
	TextureManager::Instance().draw("sky", getTransform()->position.x, getTransform()->position.y, 0, 0, false);
}

void Background::update()
{
}

void Background::clean()
{
}

