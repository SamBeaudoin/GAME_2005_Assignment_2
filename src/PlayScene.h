#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Plane.h"
#include "Player.h"
#include "Bob.h"
#include "Button.h"
#include "Label.h"

class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;
private:
	// IMGUI Function
	void GUI_Function();
	std::string m_guiTitle;
	
	glm::vec2 m_mousePosition;

	Bob* m_pProjectile;

	float t = 0;
	float gravity = -9.8;
	float angle = 74.1103854757f;
	float radians = (M_PI / 180) * -angle;
	float launchSpeed = 95;
	glm::vec2 Velocity = glm::vec2(launchSpeed*cos(radians), launchSpeed * sin(radians));
	float StartX = 50, StartY = 450;
	float X = StartX, Y = StartY;
	bool Launch = false;
	bool Launching = false;

	// UI Items
	Button* m_pBackButton;
	Button* m_pNextButton;
	Label* m_pInstructionsLabel;
	Label* m_pInstructionsLabel2;
	Label* m_pTimeLabel;
	Label* m_pDisplacementLabel;
};

#endif /* defined (__PLAY_SCENE__) */