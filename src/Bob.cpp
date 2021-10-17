#include "Bob.h"
#include "TextureManager.h"

Bob::Bob()
{
	TextureManager::Instance().load("../Assets/textures/Crate.png", "ship");

	auto size = TextureManager::Instance().getTextureSize("ship");
	setWidth(size.x);
	setHeight(size.y); 
	m_Angle = 36;
}

Bob::~Bob()
= default;

void Bob::draw()
{
	TextureManager::Instance().draw("ship", getTransform()->position.x, getTransform()->position.y - 17, m_Angle, 255, true);
}

void Bob::update()
{
}

void Bob::clean()
{
}

void Bob::SetAngle(int val)
{
	m_Angle = val;
}

